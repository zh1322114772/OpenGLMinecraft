#include "TKB_ChunkLoader.hpp"
#include "TKB_InputGetter.hpp"
#include "CFG_Blocks.hpp"
#include <thread>
#include <vector>
#include "Other.hpp"
#include <iostream>

#define PI 3.1415926
#define MAX_HEIGHT 40
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
			memset(chunkLoadRegion, false, ((MAX_RADIUS * 2) + 1) * ((MAX_RADIUS * 2) + 1));

			//set center
			chunkLoadRegion[MAX_RADIUS][MAX_RADIUS] = true;

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

					chunkLoadRegion[MAX_RADIUS + x][MAX_RADIUS + y] = true;
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

		void ChunkLoader::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			//get position
			auto position = ((InputGetter*)taskList[0])->getPosition();

			//c current center chunk
			long long centerChunkX = floor(position.x / 16);
			long long centerChunkY = floor(position.z / 16);

			//clear mask
			memset(chunkLoadedMask, false, ((MAX_RADIUS * 2) + 1) * ((MAX_RADIUS * 2) + 1));

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
						//set to loaded mask
						chunkLoadedMask[MAX_RADIUS + offsetFromCenterX][MAX_RADIUS + offsetFromCenterY] = true;
					}
				}
			
			}

			std::vector<std::thread> loadingTasks;

			//generate new chunks
			for (long long i = leftTop; i < rightBottom; i++) 
			{
				for (long long j = leftTop; j < rightBottom; j++)
				{
					//compare mask
					if (chunkLoadRegion[i][j] && !chunkLoadedMask[i][j]) 
					{
						auto chunk = recycleList.front();
						recycleList.pop();

						chunk->locationX = (i - MAX_RADIUS) + centerChunkX;
						chunk->locationY = (j - MAX_RADIUS) + centerChunkY;

						//add to loading list
						loadingTasks.push_back(std::thread(&ChunkLoader::genChunkData, this, chunk));
						activeChunkList.push_back(chunk);
					}
				
				}
			}

			//generate new chunks
			for (auto i = loadingTasks.begin(); i < loadingTasks.end(); i++) 
			{
				(*i).join();
			}

		}
		
		void ChunkLoader::genChunkData(chunkLoaderTypes::Chunk* chunk) 
		{
			//0-----1
			//|     |
			//|     |
			//3-----2
			float coordinateHeights[4];
			coordinateHeights[0] = other::Other::randomGeneratorF(seed, (chunk->locationX) * (chunk->locationY));
			coordinateHeights[1] = other::Other::randomGeneratorF(seed, (chunk->locationX + 1) * (chunk->locationY));
			coordinateHeights[2] = other::Other::randomGeneratorF(seed, (chunk->locationX + 1) * (chunk->locationY - 1));
			coordinateHeights[3] = other::Other::randomGeneratorF(seed, (chunk->locationX) * (chunk->locationY - 1));
			
			for (int x = 0; x < 16; x++) 
			{
				for (int z = 0; z < 16; z++) 
				{
					auto current = glm::vec3((float)x, 0.0, (float)z);

					float h1 = other::Other::gaussianSimilarity(glm::vec3(0.0, 0.0, 16.0), current, 7);
					float h2 = other::Other::gaussianSimilarity(glm::vec3(16.0, 0.0, 16.0), current, 7);
					float h3 = other::Other::gaussianSimilarity(glm::vec3(16.0, 0.0, 0.0), current, 7);
					float h4 = other::Other::gaussianSimilarity(glm::vec3(0.0, 0.0, 0.0), current, 7);

					int thisHeight = (((h1 * coordinateHeights[0]) + (h2 * coordinateHeights[1]) + (h3 * coordinateHeights[2]) + (h4 * coordinateHeights[3])) / 4.0) * MAX_HEIGHT;

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

			/***
			//hide invisible blocks to optimize the fps//
			using namespace game::config::resource;
			using namespace renderer::controllers::world3D;

			//init visible states
			for (int h = 0; h < 256; h++)
			{
				for (int w = 0; w < 16; w++)
				{
					unsigned int bitString = 0;
					for (int l = 0; l < 16; l++) 
					{
						bitString >>= 2;
						bitString += ((BlockMeshIDs::IDList[chunk->blocks[h][w][l].blockID]->visible) << 30);
					}

					chunk->visibleState[h][w] = bitString;
				}
			}
			
			//hide inner blocks
			unsigned int PosMask = 0b11;
			for (int h = 1; h < 255; h++)
			{
				for (int w = 1; w < 15; w++)
				{
					unsigned int bitString = chunk->visibleState[h][w];
					for (int l = 1; l < 15; l++)
					{

						//if surrounding blocks are not transparent or invisible, then hide self
						if ((BlockMeshIDs::IDList[chunk->blocks[h + 1][w][l].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[chunk->blocks[h - 1][w][l].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[chunk->blocks[h][w + 1][l].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[chunk->blocks[h][w - 1][l].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[chunk->blocks[h][w][l + 1].blockID]->visible == BlockMesh::VISIBLE) &&
							(BlockMeshIDs::IDList[chunk->blocks[h][w][l - 1].blockID]->visible == BlockMesh::VISIBLE))
						{
							bitString = (~(PosMask << (l * 2)) & bitString) + (BlockMesh::INVISIBLE << (l * 2));
						}

					}
					chunk->visibleState[h][w] = bitString;
				}
			}
			
			
			//check border blocks
			for (int h = 1; h < 255; h++)
			{
				//check 2d horizontal
				for (int w = 0; w < 16; w++) 
				{
					if ((BlockMeshIDs::IDList[chunk->blocks[h + 1][w][0].blockID]->visible == BlockMesh::VISIBLE) && 
						(BlockMeshIDs::IDList[chunk->blocks[h - 1][w][0].blockID]->visible == BlockMesh::VISIBLE)) 
					{
						chunk->visibleState[h][w] = (chunk->visibleStates[h][w] & 0b11111111111111111111111111111100) + (BlockMesh::INVISIBLE);
					}

					if ((BlockMeshIDs::IDList[chunk->blocks[h + 1][w][15].blockID]->visible == BlockMesh::VISIBLE) &&
						(BlockMeshIDs::IDList[chunk->blocks[h - 1][w][15].blockID]->visible == BlockMesh::VISIBLE))
					{
						chunk->visibleState[h][w] = (chunk->visibleStates[h][w] & 0b00111111111111111111111111111111) + (BlockMesh::INVISIBLE << 30);
					}					
				}
				
				//check 2d vertical
				unsigned int bitString0 = chunk->visibleState[h][0];
				unsigned int bitString1 = chunk->visibleState[h][15];

				for (int l = 1; l < 15; l++) 
				{
					if ((BlockMeshIDs::IDList[chunk->blocks[h + 1][0][l].blockID]->visible == BlockMesh::VISIBLE) &&
						(BlockMeshIDs::IDList[chunk->blocks[h - 1][0][l].blockID]->visible == BlockMesh::VISIBLE))
					{
						bitString0 = (~(PosMask << (l * 2)) & bitString0) + (BlockMesh::INVISIBLE << (l * 2));
					}

					if ((BlockMeshIDs::IDList[chunk->blocks[h + 1][15][l].blockID]->visible == BlockMesh::VISIBLE) &&
						(BlockMeshIDs::IDList[chunk->blocks[h - 1][15][l].blockID]->visible == BlockMesh::VISIBLE))
					{
						bitString1 = (~(PosMask << (l * 2)) & bitString1) + (BlockMesh::INVISIBLE << (l * 2));
					}
				
				}

				chunk->visibleState[h][0] = bitString0;
				chunk->visibleState[h][15] = bitString1;
				
			}
			
			//set slice visible
			for (int h = 0; h < 256; h++) 
			{
				unsigned short int bitString = 0;
				for (int w = 0; w < 16; w++)
				{
					bool hasVisible = false;
					unsigned int visibleBitString = chunk->visibleState[h][w];

					for (int l = 0; l < 16; l++) 
					{
						if ((visibleBitString & PosMask) == BlockMesh::VISIBLE) 
						{
							hasVisible = true;
							break;
						}
						visibleBitString >>= 2;
					}

					//write data 
					bitString >>= 1;
					bitString += (hasVisible << 15);
				}

				chunk->sliceVisible[h] = bitString;
			}
			***/

			//set active 
			chunk->isActive = true;
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