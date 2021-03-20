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
		
		float ChunkLoader::getSimilarityMix(unsigned long long seed, float topLeftX, float topLeftY, float size, float flatness,float currentX, float currentY) 
		{
			//0-----1
			//|     |
			//|     |
			//3-----2
			glm::vec4 coordinateHeights;
			glm::vec4 similarity;
			glm::vec2 currentPos(currentX, currentY);

			long long px = (long long)topLeftX;
			long long py = (long long)topLeftY;

			coordinateHeights[0] = other::Other::randomGeneratorF(seed, XYtoX(px, py)) * flatness;
			coordinateHeights[1] = other::Other::randomGeneratorF(seed, XYtoX((px + 1), py)) * flatness;
			coordinateHeights[2] = other::Other::randomGeneratorF(seed, XYtoX((px + 1), (py - 1))) * flatness;
			coordinateHeights[3] = other::Other::randomGeneratorF(seed, XYtoX(px, (py - 1))) * flatness;

			similarity[0] = other::Other::gaussianSimilarity(glm::vec2(0.0, size - 1), currentPos, size / 2);
			similarity[1] = other::Other::gaussianSimilarity(glm::vec2(size - 1, size - 1), currentPos, size / 2);
			similarity[2] = other::Other::gaussianSimilarity(glm::vec2(size - 1, 0.0), currentPos, size / 2);
			similarity[3] = other::Other::gaussianSimilarity(glm::vec2(0.0, 0.0), currentPos, size / 2);

			auto nonLinearSimilarity = (6.0f * glm::pow(similarity, glm::vec4(5.0))) - (15.0f * glm::pow(similarity, glm::vec4(4.0))) + (10.0f * glm::pow(similarity, glm::vec4(3.0)));

			float mixHeight = glm::dot(coordinateHeights, nonLinearSimilarity) / 4.0;
			
			return mixHeight;
		}

		void ChunkLoader::genChunkData(chunkLoaderTypes::Chunk* chunk) 
		{

			for (int x = 0; x < 16; x++) 
			{
				for (int z = 0; z < 16; z++) 
				{
					float currentX = ((chunk->locationX * 16) + x) - (floorf((float)chunk->locationX / 4) * 64);
					float currentY = ((chunk->locationY * 16) + z) - (floorf((float)chunk->locationY / 4) * 64);

					float region = getSimilarityMix(seed + 123456, floorf((float)chunk->locationX / 4), floorf((float)chunk->locationY / 4), 64, 1.4, currentX, currentY);
					//float flatness = getSimilarityMix(seed, chunk->locationX, chunk->locationY, 16, 0.2 , x, z);

					//std::cout << ((flatness * 0.5) - 0.4) << std::endl;

					int thisHeight = (0.3 + (region * 0.5)) * MAX_HEIGHT;

					for (int y = 0; y < 256; y++) 
					{
						if (y > thisHeight)
						{
							chunk->blocks[y][x][z] = game::config::blocks::AirBlock();
						}
						else 
						{
							chunk->blocks[y][x][z] = game::config::blocks::OakPlankBlock();
						}
					}
				}
			}

		}

		void ChunkLoader::hideBlocks(chunkLoaderTypes::Chunk* chunk, long long x, long long y) 
		{
			//hide invisible blocks to optimize the fps//
			using namespace game::config::resource;
			using namespace renderer::controllers::world3D;
			using namespace std::chrono;

			//init visible states
			for (int h = 0; h < 256; h++)
			{
				for (int w = 0; w < 16; w++)
				{
					for (int l = 0; l < 16; l++)
					{
						chunk->blockVisible[h][w][l] = (BlockMeshIDs::IDList[chunk->blocks[h][w][l].blockID]->visible != BlockMesh::INVISIBLE);
					}
				}
			}



			//hide inner blocks

			for (int h = 1; h < 255; h++)
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

						//if surrounding blocks are not transparent or invisible, then hide self
						if ((BlockMeshIDs::IDList[chunk->blocks[h + 1][w][l].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[chunk->blocks[h - 1][w][l].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[right->blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[left->blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[forward->blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[backward->blockID]->visible == BlockMesh::VISIBLE))
						{
							chunk->blockVisible[h][w][l] = false;
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