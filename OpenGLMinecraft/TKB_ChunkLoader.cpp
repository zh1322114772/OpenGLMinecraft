#include "TKB_ChunkLoader.hpp"
#include "TKB_InputGetter.hpp"
#include "Other.hpp"

#include <thread>
#include <vector>
#include <iostream>
#include <chrono>

#define PI 3.1415926
#define MAX_HEIGHT 200
#include "math.h"
#include "BitMask.hpp"

using namespace global::resource;

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
			//current center position
			auto position = ((InputGetter*)taskList[0])->getPosition();
			long long centerChunkX = floor(position.x / 16);
			long long centerChunkY = floor(position.z / 16);

			//clear map
			memset(chunkLoadingMap, false, ((MAX_RADIUS * 2) + 1) * ((MAX_RADIUS * 2) + 1) * sizeof(chunkLoaderTypes::Chunk*));
			edgeList.clear();

			//re-range chunks
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
						activeChunkList[i]->edge = false;

						recycleList.push(activeChunkList[i]);
						activeChunkList.erase(activeChunkList.begin() + i);
					}
					else
					{
						//map to index
						chunkLoadingMap[MAX_RADIUS + offsetFromCenterX][MAX_RADIUS + offsetFromCenterY] = activeChunkList[i];
						//if need to be re-updated
						if (activeChunkList[i]->edge) 
						{
							edgeList.push_back(activeChunkList[i]);
						}
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
				tasks.clear();

				//map chunk positions to position map
				while (!newGeneratedChunks.empty()) 
				{
					auto i = newGeneratedChunks.front();
					newGeneratedChunks.pop();

					long long x = (i->locationX - centerChunkX) + MAX_RADIUS;
					long long y = (i->locationY - centerChunkY) + MAX_RADIUS;

					chunkLoadingMap[x][y] = i;
					tasks.push_back(std::thread(&ChunkLoader::hideBlocks, this, i, x, y));
				}

				//check edge chunks that's eligible to be re-updated
				for (auto i = edgeList.begin(); i < edgeList.end(); i++) 
				{
					long long x = ((*i)->locationX - centerChunkX) + MAX_RADIUS;
					long long y = ((*i)->locationY - centerChunkY) + MAX_RADIUS;

					if (!chunkLoadingMap[x + 1][y]) 
					{
						continue;
					}
					if (!chunkLoadingMap[x - 1][y])
					{
						continue;
					}
					if (!chunkLoadingMap[x][y + 1])
					{
						continue;
					}
					if (!chunkLoadingMap[x][y - 1])
					{
						continue;
					}

					tasks.push_back(std::thread(&ChunkLoader::hideBlocks, this, *i, x, y));
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

		void ChunkLoader::verticalInfoGenerator(std::tuple<int, int, blocks::Block>* info, int& counter, long long chunkX, long long chunkY, int x, int z)
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
				info[counter++] = std::make_tuple(0, thisHeight, blocks::CobbleStoneBlock());
			}
			else 
			{
				//add terrain
				info[counter++] = std::make_tuple(0, thisHeight, blocks::GrassBlock());
			}


			//check if terrain is above the sea level
			if (thisHeight < 75) 
			{
				info[counter++] = std::make_tuple(thisHeight, 75, blocks::WaterBlock());
			}
		
		}

		void ChunkLoader::genChunkData(chunkLoaderTypes::Chunk* chunk) 
		{

			std::tuple<int, int, blocks::Block>* verticalInfo = new std::tuple<int, int, blocks::Block>[255];
			int infoCounter = 0;

			for (int x = 0; x < 16; x++) 
			{
				for (int z = 0; z < 16; z++) 
				{

					verticalInfoGenerator(verticalInfo, infoCounter, chunk->locationX, chunk->locationY, x, z);
					
					//add air as last layer
					auto [h0, h1, blkType] = verticalInfo[infoCounter - 1];
					verticalInfo[infoCounter++] = std::make_tuple(h1, 256, blocks::AirBlock());

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
			using namespace renderer::controllers::world3DTypes;
			using namespace std::chrono;

			//clear block counter
			memset(chunk->blockCounter, 0, CFG_BLOCKMESH_ID_LAST * sizeof(unsigned short int));

			//reset current state
			chunk->edge = false;
			
			//hide inner blocks
			for (int h = 0; h < 255; h++)
			{
				for (int w = 0; w < 16; w++)
				{
					for (int l = 0; l < 16; l++)
					{
						//current block properties
						auto blkThis = BlockMeshIDs::IDList[chunk->blocks[h][w][l].blockID]->properties;

						//if block is already invisble then skip
						if (GET_BIT1(blkThis) == BlockMesh::ATTACHMENT_INVISIBLE)
						{
							chunk->blockVisibleState[h][w][l] = 0b111111;
							continue;
						}
		
						//make bottom invisible
						if (h == 0) 
						{
							chunk->blockVisibleState[h][w][l] = 0b111111;
							continue;
						}

						//surrounding block properties
						auto blkAbove = BlockMeshIDs::IDList[chunk->blocks[h + 1][w][l].blockID]->properties;
						auto blkBelow = BlockMeshIDs::IDList[chunk->blocks[h - 1][w][l].blockID]->properties;;
						auto blkRight = blkThis;
						auto blkLeft = blkThis;
						auto blkFront = blkThis;
						auto blkBack = blkThis;

						//get back block
						if (l >= 15) 
						{
							if (chunkLoadingMap[x][y + 1] != nullptr) 
							{
								blkBack = BlockMeshIDs::IDList[chunkLoadingMap[x][y + 1]->blocks[h][w][0].blockID]->properties;
							}
							else 
							{
								chunk->edge = true;
							}
	
						}
						else 
						{
							blkBack = BlockMeshIDs::IDList[chunk->blocks[h][w][l + 1].blockID]->properties;
						}

						//get front block
						if (l <= 0) 
						{
							if (chunkLoadingMap[x][y - 1] != nullptr)
							{
								blkFront = BlockMeshIDs::IDList[chunkLoadingMap[x][y - 1]->blocks[h][w][15].blockID]->properties;
							}
							else 
							{
								chunk->edge = true;
							}
							
						}
						else 
						{
							blkFront = BlockMeshIDs::IDList[chunk->blocks[h][w][l - 1].blockID]->properties;
						}

						//get right block
						if (w >= 15) 
						{
							if (chunkLoadingMap[x + 1][y] != nullptr)
							{
								blkRight = BlockMeshIDs::IDList[chunkLoadingMap[x + 1][y]->blocks[h][0][l].blockID]->properties;
							}else
							{
								chunk->edge = true;
							}
						
						}
						else 
						{
							blkRight = BlockMeshIDs::IDList[chunk->blocks[h][w + 1][l].blockID]->properties;
						}

						//get left block
						if (w <= 0) 
						{
							if (chunkLoadingMap[x - 1][y] != nullptr)
							{
								blkLeft = BlockMeshIDs::IDList[chunkLoadingMap[x - 1][y]->blocks[h][15][l].blockID]->properties;
							}
							else 
							{
								chunk->edge = true;
							}
						}
						else 
						{
							blkLeft = BlockMeshIDs::IDList[chunk->blocks[h][w - 1][l].blockID]->properties;
						}

						bool invisibleAbove;
						bool invisibleBelow;
						bool invisibleRight;
						bool invisibleLeft;
						bool invisibleFront;
						bool invisibleBack;
						unsigned char invisibleFaces = 0;

						//check block type
						if ((blkThis & 0b1) == BlockMesh::TYPE_BLOCK) 
						{
							invisibleAbove = ((GET_BIT1(blkAbove) == BlockMesh::ATTACHMENT_VISIBLE)) && ((GET_BIT0(blkAbove) == BlockMesh::TYPE_BLOCK));
							invisibleBelow = ((GET_BIT1(blkBelow) == BlockMesh::ATTACHMENT_VISIBLE)) && ((GET_BIT0(blkBelow) == BlockMesh::TYPE_BLOCK));
							invisibleRight = ((GET_BIT1(blkRight) == BlockMesh::ATTACHMENT_VISIBLE)) && ((GET_BIT0(blkRight) == BlockMesh::TYPE_BLOCK));
							invisibleLeft = ((GET_BIT1(blkLeft) == BlockMesh::ATTACHMENT_VISIBLE)) && ((GET_BIT0(blkLeft) == BlockMesh::TYPE_BLOCK));
							invisibleFront = ((GET_BIT1(blkFront) == BlockMesh::ATTACHMENT_VISIBLE)) && ((GET_BIT0(blkFront) == BlockMesh::TYPE_BLOCK));
							invisibleBack = ((GET_BIT1(blkBack) == BlockMesh::ATTACHMENT_VISIBLE)) && ((GET_BIT0(blkBack) == BlockMesh::TYPE_BLOCK));			
						}
						else 
						{
							invisibleAbove = (GET_BIT1(blkAbove) == BlockMesh::ATTACHMENT_VISIBLE);
							invisibleBelow = (GET_BIT1(blkBelow) == BlockMesh::ATTACHMENT_VISIBLE);
							invisibleRight = (GET_BIT1(blkRight) == BlockMesh::ATTACHMENT_VISIBLE);
							invisibleLeft = (GET_BIT1(blkLeft) == BlockMesh::ATTACHMENT_VISIBLE);
							invisibleFront = (GET_BIT1(blkFront) == BlockMesh::ATTACHMENT_VISIBLE);
							invisibleBack = (GET_BIT1(blkBack) == BlockMesh::ATTACHMENT_VISIBLE);					
						}

						//update visible state
						invisibleFaces = SET_BIT0(invisibleBack) + SET_BIT1(invisibleLeft) + SET_BIT2(invisibleFront) + SET_BIT3(invisibleRight) + SET_BIT4(invisibleAbove) + SET_BIT5(invisibleBelow);
						chunk->blockVisibleState[h][w][l] = invisibleFaces;
						chunk->blockCounter[chunk->blocks[h][w][l].blockID] += (invisibleFaces != 0b111111);
					}
				}
			}

			//std::cout << chunk->edge << std::endl;
			//set active 
			chunk->isActive = true;
			chunk->updateTime = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
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