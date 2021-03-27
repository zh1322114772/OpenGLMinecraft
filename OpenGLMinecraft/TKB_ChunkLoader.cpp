#include "TKB_ChunkLoader.hpp"
#include "TKB_InputGetter.hpp"
#include "CFG_Blocks.hpp"
#include <thread>
#include <vector>
#include "Other.hpp"
#include <iostream>
#include <chrono>

#define PI 3.1415926
#define MAX_HEIGHT 200
#include "math.h"
namespace tickerable
{
	namespace tasks
	{

		int ChunkLoader::getChunkListSize() 
		{
			return chunkListSize;
		}

		chunkLoaderTypes::Chunk** ChunkLoader::getChunkList() 
		{
			return chunkList;
		}

		const std::vector<chunkLoaderTypes::Chunk*>& ChunkLoader::getActiveList()
		{
			return activeChunkList;
		}

		ChunkLoader::ChunkLoader(const int v, unsigned long long s) : viewDistance(v), seed(s)
		{
			if (viewDistance >= MAX_RADIUS) 
			{
				throw std::runtime_error("View distance exceed the maximum allowable radius");
			}


			chunkListSize = (int)(std::pow((viewDistance), 2) * PI);
			chunkList = new chunkLoaderTypes::Chunk* [chunkListSize];

			//assign space for chunks
			for (int i = 0; i < chunkListSize; i++)
			{
				chunkList[i] = new chunkLoaderTypes::Chunk();
				chunkList[i]->chunkID = i;
				recycleList.push(chunkList[i]);
			}

			//init template to false
			memset(chunkRegionMap, false, ((MAX_RADIUS * 2) + 1) * ((MAX_RADIUS * 2) + 1));

			//set center
			chunkRegionMap[MAX_RADIUS][MAX_RADIUS] = true;

			//generate chunk loading template
			for (int i = 1; i < viewDistance; i++) 
			{
				int c = floorf((float)(i * 2) * PI) * 2;
				float deltaRad = (2 * PI) / c;
				float currentRad = 0;

				//fill circle
				for (int j = 0; j < c; j++) 
				{
					int y = sinf(currentRad) * i;
					int x = cosf(currentRad) * i;

					chunkRegionMap[MAX_RADIUS + x][MAX_RADIUS + y] = true;
					currentRad += deltaRad;
				}
			}

			//set boundaries
			leftTop = MAX_RADIUS - viewDistance;
			rightBottom = leftTop + ((viewDistance * 2) + 1);

		}

		void ChunkLoader::onEnable() 
		{
		
		}

		void ChunkLoader::onDisable() 
		{
		
		
		}

		void ChunkLoader::onExit() 
		{
		
		}

		long long ChunkLoader::XYtoX(long long x, long long y) 
		{

			long long z1 = ((x << 6) ^ y) + (x | (y << 5)) + ((x << 4) & y) + (x ^ (y << 3)) + ((x << 2) | y) + (x & (y << 1));

			return z1;
		}

		void ChunkLoader::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			//get position
			auto position = ((InputGetter*)taskList[0])->getPosition();

			//c current center chunk
			long long centerChunkX = floor(position.x / 16);
			long long centerChunkY = floor(position.z / 16);

			//clear map
			memset(chunkLoadingMap, false, ((MAX_RADIUS * 2) + 1) * ((MAX_RADIUS * 2) + 1));

			//check if existence chunks are still in range
			if (activeChunkList.size() > 0) 
			{
				for (int i = activeChunkList.size() - 1; i >= 0; i--)
				{

					long long offsetFromCenterX = (activeChunkList[i])->locationX - centerChunkX;
					long long offsetFromCenterY = (activeChunkList[i])->locationY - centerChunkY;
					int distanceFromCenter = (int)sqrtf(powf(offsetFromCenterX, 2) + powf(offsetFromCenterY, 2));

					//check if it's out of view distance
					if (distanceFromCenter >= viewDistance)
					{
						//add to recycle list
						activeChunkList[i]->isActive = false;
						recycleList.push(activeChunkList[i]);
						activeChunkList.erase(activeChunkList.begin() + i);
					}
					else
					{
						//set to loading map
						chunkLoadingMap[MAX_RADIUS + offsetFromCenterX][MAX_RADIUS + offsetFromCenterY] = true;
					}
				}
			
			}

			std::vector<std::thread> tasks;
			std::queue<chunkLoaderTypes::Chunk*> newGeneratedChunks;


			//generate new chunks
			for (long long i = leftTop; i < rightBottom; i++) 
			{
				for (long long j = leftTop; j < rightBottom; j++)
				{
					//compare template map and loading map
					if (chunkRegionMap[i][j] && !chunkLoadingMap[i][j]) 
					{
						auto chunk = recycleList.front();
						recycleList.pop();

						chunk->locationX = (i - MAX_RADIUS) + centerChunkX;
						chunk->locationY = (j - MAX_RADIUS) + centerChunkY;
					

						//add to loading list
						tasks.push_back(std::thread(&ChunkLoader::genChunkData, this, chunk));
						newGeneratedChunks.push(chunk);
						activeChunkList.push_back(chunk);
					}
				
				}
			}

			//run multithreads
			for (auto i = tasks.begin(); i < tasks.end(); i++)
			{
				(*i).join();
			}


			//hide inner blocks
			if (!newGeneratedChunks.empty()) 
			{
				//clear map and threads
				memset(chunkPositionMap, 0, ((MAX_RADIUS * 2) + 1) * ((MAX_RADIUS * 2) + 1) * sizeof(chunkLoaderTypes::Chunk*));
				tasks.clear();

				//map chunk positions to position map
				while (!newGeneratedChunks.empty()) 
				{
					auto i = newGeneratedChunks.front();
					newGeneratedChunks.pop();

					long long x = (i->locationX - centerChunkX) + MAX_RADIUS;
					long long y = (i->locationY - centerChunkY) + MAX_RADIUS;

					chunkPositionMap[x][y] = i;
					tasks.push_back(std::thread(&ChunkLoader::hideBlocks, this, i, x, y));
				}

				//run multithreads
				for (auto i = tasks.begin(); i < tasks.end(); i++)
				{
					(*i).join();
				}
			}
		}
		
		std::tuple<float, glm::vec4, glm::vec4> ChunkLoader::getSimilarityMix(unsigned long long seed, float topLeftX, float topLeftY, float flatness, int samplingRange, float blockX, float blockZ, float select, glm::vec4 selectBias)
		{
			//0-----1
			//|     |
			//|     |
			//3-----2
			float size = 16 * samplingRange;
			long long px = (long long)floorf(topLeftX / samplingRange);
			long long py = (long long)floorf(topLeftY / samplingRange);
			glm::vec4 coordinateHeights(0.0f);
			glm::vec4 similarity(0.0f);
			glm::vec4 thresholds(1.0);

			if (other::Other::randomGeneratorF(seed * 1024, XYtoX(px, py)) < (1 - select))
			{
				thresholds[0] = 0;
			}

			if (other::Other::randomGeneratorF(seed * 1024, XYtoX(px + 1, py)) < (1 - select))
			{
				thresholds[1] = 0;
			}

			if (other::Other::randomGeneratorF(seed * 1024, XYtoX(px + 1, py - 1)) < (1 - select))
			{
				thresholds[2] = 0;
			}

			if (other::Other::randomGeneratorF(seed * 1024, XYtoX(px, py - 1)) < (1 - select))
			{
				thresholds[3] = 0;
			}

			//add bias to threshold
			thresholds += selectBias;
			glm::vec2 currentPos((((topLeftX * 16) + blockX) - (px * size)) / size, (((topLeftY * 16) + blockZ) - (py * size)) / size);

			coordinateHeights[0] = other::Other::randomGeneratorF(seed, XYtoX(px, py)) * flatness;
			coordinateHeights[1] = other::Other::randomGeneratorF(seed, XYtoX((px + 1), py)) * flatness;
			coordinateHeights[2] = other::Other::randomGeneratorF(seed, XYtoX((px + 1), (py - 1))) * flatness;
			coordinateHeights[3] = other::Other::randomGeneratorF(seed, XYtoX(px, (py - 1))) * flatness;

			coordinateHeights = coordinateHeights * thresholds;

			similarity[0] = other::Other::gaussianSimilarity(glm::vec2(0, 1), currentPos, 0.5);
			similarity[1] = other::Other::gaussianSimilarity(glm::vec2(1, 1), currentPos, 0.5);
			similarity[2] = other::Other::gaussianSimilarity(glm::vec2(1, 0), currentPos, 0.5);
			similarity[3] = other::Other::gaussianSimilarity(glm::vec2(0, 0), currentPos, 0.5);

			auto nonLinearSimilarity = (glm::pow(similarity, glm::vec4(3.0)));

			float mixHeight = glm::dot(coordinateHeights, nonLinearSimilarity) / 4.0;
			
			return std::make_tuple(mixHeight, coordinateHeights, similarity);
		}

		void ChunkLoader::verticalInfoGenerator(std::tuple<int, int,game::config::blocks::Block>* info, int& counter, long long chunkX, long long chunkY, int x, int z)
		{

			//generate region
			auto[reg, rc, rs] = getSimilarityMix(seed, chunkX, chunkY, 6, 96, x, z);
			auto[reg1, rc1, rs1] = getSimilarityMix(seed * 2, chunkX, chunkY, 6, 48, x, z);
			auto [reg2, rc2, rs2] = getSimilarityMix(seed * 3, chunkX, chunkY, 6, 24, x, z);
			auto [reg3, rc3, rs3] = getSimilarityMix(seed * 4, chunkX, chunkY, 6, 12, x, z);
			auto [reg4, rc4, rs4] = getSimilarityMix(seed * 5, chunkX, chunkY, 6, 6, x, z);
			auto [reg5, rc5, rs5] = getSimilarityMix(seed * 6, chunkX, chunkY, 6, 3, x, z);
			auto [reg6, rc6, rs6] = getSimilarityMix(seed * 7, chunkX, chunkY, 6, 1, x, z);
			float region = (reg * 0.5) + (reg1 * 0.25) + (reg2 * 0.125) + (reg3 * 0.0625) + (reg4 * 0.03125) + (reg5 * 0.015625) + (reg6 * 0.0078125);

			//generate mountains
			float mountain = 0;
			auto[mreg, mrc, mrs] = getSimilarityMix(seed * 8, chunkX, chunkY, 5.5, 48, x, z);
			auto [mreg1, mrc1, mrs1] = getSimilarityMix(seed * 9, chunkX, chunkY, 3, 16, x, z);
			auto [mreg2, mrc2, mrs2] = getSimilarityMix(seed * 10, chunkX, chunkY, 2, 4, x, z);
			auto [mreg3, mrc3, mrs3] = getSimilarityMix(seed * 11, chunkX, chunkY, 1, 1, x, z);
			float mountainCandidateRegion = other::Other::relu(powf((mreg + mreg1 + mreg2 + mreg3), 2), 1.0);
			mountainCandidateRegion = other::Other::smooth(mountainCandidateRegion, 1);

			auto[mount, mountrc, mountrs] = getSimilarityMix(seed * 12, chunkX, chunkY, 5, 8, x, z, 0.0, glm::vec4(mountainCandidateRegion));
			auto [mount1, mountrc1, mountrs1] = getSimilarityMix(seed * 13, chunkX, chunkY, 5, 4, x, z, 0.0, glm::vec4(mount));
			auto [mount2, mountrc2, mountrs2] = getSimilarityMix(seed * 14, chunkX, chunkY, 4, 2, x, z, 0.0, glm::vec4(mount1));
			auto [mount3, mountrc3, mountrs3] = getSimilarityMix(seed * 14, chunkX, chunkY, 3, 1, x, z, 0.0, glm::vec4(mount2));

			mountain = (mount * 0.5) + (mount1 * 0.25) + (mount2 * 0.125) + (mount3 * 0.0625);

			int thisHeight = (0.1 + (region * 0.5) + (mountain * 0.25)) * MAX_HEIGHT;
			//set counter to zero
			counter = 0;

			if (mountainCandidateRegion > 0) 
			{
				//add terrain
				info[counter++] = std::make_tuple(0, thisHeight, game::config::blocks::CobbleStoneBlock());
			}
			else 
			{
				//add terrain
				info[counter++] = std::make_tuple(0, thisHeight, game::config::blocks::GrassBlock());
			}


			//check if terrain is above the sea level
			if (thisHeight < 75) 
			{
				info[counter++] = std::make_tuple(thisHeight, 75, game::config::blocks::WaterBlock());
			}
		
		}

		void ChunkLoader::genChunkData(chunkLoaderTypes::Chunk* chunk) 
		{

			std::tuple<int, int, game::config::blocks::Block>* verticalInfo = new std::tuple<int, int, game::config::blocks::Block>[255];
			int infoCounter = 0;

			for (int x = 0; x < 16; x++) 
			{
				for (int z = 0; z < 16; z++) 
				{

					verticalInfoGenerator(verticalInfo, infoCounter, chunk->locationX, chunk->locationY, x, z);
					
					//add air as last layer
					auto [h0, h1, blkType] = verticalInfo[infoCounter - 1];
					verticalInfo[infoCounter++] = std::make_tuple(h1, 256, game::config::blocks::AirBlock());

					//each each layer
					for (int j = 0; j < infoCounter; j++) 
					{
						auto [h0, h1, blk] = verticalInfo[j];

						for (int y = h0; y < h1; y++) 
						{
							chunk->blocks[y][x][z] = blk;
						}

					}

				}
			}

			delete[] verticalInfo;
		}

		void ChunkLoader::hideBlocks(chunkLoaderTypes::Chunk* chunk, long long x, long long y) 
		{
			//hide invisible blocks to optimize the fps//
			using namespace game::config::resource;
			using namespace renderer::controllers::world3D;
			using namespace std::chrono;

			//clear block counter
			memset(chunk->blockCounter, 0, CFG_BLOCKMESH_ID_LAST * sizeof(unsigned short int));


			//init visible states
			for (int h = 0; h < 256; h++)
			{
				for (int w = 0; w < 16; w++)
				{
					for (int l = 0; l < 16; l++)
					{
						if (BlockMeshIDs::IDList[chunk->blocks[h][w][l].blockID]->visible != BlockMesh::INVISIBLE) 
						{
							//either visible , transparnt , reflect
							chunk->blockVisible[h][w][l] = true;
						}
						else 
						{
							// invisible
							chunk->blockVisible[h][w][l] = false;
						}

					}
				}
			}

			
			//hide inner blocks
			for (int h = 0; h < 255; h++)
			{
				for (int w = 0; w < 16; w++)
				{
					for (int l = 0; l < 16; l++)
					{
						//if block is already invisble then skip
						if (BlockMeshIDs::IDList[chunk->blocks[h][w][l].blockID]->visible == BlockMesh::INVISIBLE) 
						{
							continue;
						}
		
						//clean bottom 
						if (h == 0) 
						{
							chunk->blockVisible[h][w][l] = false;
							continue;
						}

						game::config::blocks::Block* forward = &chunk->blocks[h][w][l];
						game::config::blocks::Block* backward = &chunk->blocks[h][w][l];
						game::config::blocks::Block* left = &chunk->blocks[h][w][l];
						game::config::blocks::Block* right = &chunk->blocks[h][w][l];

						//get forward block
						if (l >= 15) 
						{
							if (chunkPositionMap[x][y + 1] != nullptr) 
							{
								forward = &chunkPositionMap[x][y + 1]->blocks[h][w][0];
							}
	
						}
						else 
						{
							forward = &chunk->blocks[h][w][l + 1];
						}

						//get backword block
						if (l <= 0) 
						{
							if (chunkPositionMap[x][y - 1] != nullptr) 
							{
								backward = &chunkPositionMap[x][y - 1]->blocks[h][w][15];
							}
							
						}
						else 
						{
							backward = &chunk->blocks[h][w][l - 1];
						}

						//get right block
						if (w >= 15) 
						{
							if (chunkPositionMap[x + 1][y] != nullptr) 
							{
								right = &chunkPositionMap[x + 1][y]->blocks[h][0][l];
							}
						
						}
						else 
						{
							right = &chunk->blocks[h][w + 1][l];
						}

						//get left block
						if (w <= 0) 
						{
							if (chunkPositionMap[x - 1][y] != nullptr)
							{
								left = &chunkPositionMap[x - 1][y]->blocks[h][15][l];
							}
						}
						else 
						{
							left = &chunk->blocks[h][w - 1][l];
						}

						auto blkAbove = BlockMeshIDs::IDList[chunk->blocks[h + 1][w][l].blockID]->visible;
						auto blkBelow = BlockMeshIDs::IDList[chunk->blocks[h - 1][w][l].blockID]->visible;
						auto blkRight = BlockMeshIDs::IDList[right->blockID]->visible;
						auto blkLeft = BlockMeshIDs::IDList[left->blockID]->visible;
						auto blkForward = BlockMeshIDs::IDList[forward->blockID]->visible;
						auto blkBackward = BlockMeshIDs::IDList[backward->blockID]->visible;
						auto blkThis = BlockMeshIDs::IDList[chunk->blocks[h][w][l].blockID]->visible;

						if (blkThis != BlockMesh::RELFECT) 
						{
							//if surrounding blocks are not transparent or invisible, then hide self
							if ((blkAbove == BlockMesh::VISIBLE) &&
								(blkBelow == BlockMesh::VISIBLE) &&
								(blkRight == BlockMesh::VISIBLE) &&
								(blkLeft == BlockMesh::VISIBLE) &&
								(blkForward == BlockMesh::VISIBLE) &&
								(blkBackward == BlockMesh::VISIBLE))
							{
								chunk->blockVisible[h][w][l] = false;
							}
							else
							{
								chunk->blockCounter[chunk->blocks[h][w][l].blockID]++;
							}
						}
						else 
						{
							//if surrounding blocks are visible or reflect, then hide self
							if (((blkAbove == BlockMesh::VISIBLE) || (blkAbove == BlockMesh::RELFECT))&&
								((blkBelow == BlockMesh::VISIBLE) || (blkBelow == BlockMesh::RELFECT)) &&
								((blkRight == BlockMesh::VISIBLE) || (blkRight == BlockMesh::RELFECT)) &&
								((blkLeft == BlockMesh::VISIBLE) || (blkLeft == BlockMesh::RELFECT)) &&
								((blkForward == BlockMesh::VISIBLE) || (blkForward == BlockMesh::RELFECT)) &&
								((blkBackward == BlockMesh::VISIBLE) || (blkBackward == BlockMesh::RELFECT)))
							{
								chunk->blockVisible[h][w][l] = false;
							}
							else
							{
								chunk->blockCounter[chunk->blocks[h][w][l].blockID]++;
							}
						}
					}
				}
			}

			//set active 
			chunk->isActive = true;
			chunk->timeStamp = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
		}


		ChunkLoader::~ChunkLoader() 
		{
			for (int i = 0; i < chunkListSize; i++) 
			{
				delete chunkList[i];
			}
		}

	}
}