#include "TKB_ChunkLoader.hpp"
#include "TKB_InputGetter.hpp"
#include "CFG_Blocks.hpp"

#include <iostream>

#define PI 3.1415926
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

		ChunkLoader::ChunkLoader(const int v) : viewDistance(v) 
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

						
						genChunkData(chunk, (i - MAX_RADIUS) + centerChunkX, (j - MAX_RADIUS) + centerChunkY);
						activeChunkList.push_back(chunk);
					}
				
				}
			}

		}
		
		void ChunkLoader::genChunkData(chunkLoaderTypes::Chunk* chunk, long long locX, long long locY) 
		{

			// test purpose
			for (int h = 0; h < 256; h++) 
			{
				if (h > 5) 
				{
					for (int w = 0; w < 16; w++) 
					{
						for (int l = 0; l < 16; l++) 
						{
							chunk->blocks[h][w][l] = game::config::blocks::AirBlock();
							//hide air block
							chunk->blocks[h][w][l].hide = true;
						}
					}
				}
				else 
				{
					for (int w = 0; w < 16; w++)
					{
						for (int l = 0; l < 16; l++)
						{
							chunk->blocks[h][w][l] = game::config::blocks::DirtBlock();
							chunk->blocks[h][w][l].hide = false;
						}
					}
				
				}
			
			}

			//hide inner blocks
			for (int h = 1; h < 255; h++) 
			{
				for (int w = 1; w < 15; w++) 
				{
					for (int l = 1; l < 15; l++) 
					{

						//if surrounding blocks are not air, then hide
						if ((chunk->blocks[h + 1][w][l].blockID != CFG_BLOCKMESH_ID_AIR) &&
							(chunk->blocks[h - 1][w][l].blockID != CFG_BLOCKMESH_ID_AIR) &&
							(chunk->blocks[h][w + 1][l].blockID != CFG_BLOCKMESH_ID_AIR) &&
							(chunk->blocks[h][w - 1][l].blockID != CFG_BLOCKMESH_ID_AIR) &&
							(chunk->blocks[h][w][l + 1].blockID != CFG_BLOCKMESH_ID_AIR) &&
							(chunk->blocks[h][w][l - 1].blockID != CFG_BLOCKMESH_ID_AIR)) 
						{
							chunk->blocks[h][w][l].hide = true;
						}

					}
				}
			}

			//hide border blocks
			for (int h = 1; h < 255; h++) 
			{
				for (int w = 0; w < 16; w++) 
				{
					if ((chunk->blocks[h + 1][w][0].blockID != CFG_BLOCKMESH_ID_AIR) && (chunk->blocks[h - 1][w][0].blockID != CFG_BLOCKMESH_ID_AIR)) 
					{
						chunk->blocks[h][w][0].hide = true;
					}

					if ((chunk->blocks[h + 1][w][15].blockID != CFG_BLOCKMESH_ID_AIR) && (chunk->blocks[h - 1][w][15].blockID != CFG_BLOCKMESH_ID_AIR))
					{
						chunk->blocks[h][w][15].hide = true;
					}
				}

				for (int l = 1; l < 15; l++) 
				{
					if ((chunk->blocks[h + 1][0][l].blockID != CFG_BLOCKMESH_ID_AIR) && (chunk->blocks[h - 1][0][l].blockID != CFG_BLOCKMESH_ID_AIR))
					{
						chunk->blocks[h][0][l].hide = true;
					}

					if ((chunk->blocks[h + 1][15][l].blockID != CFG_BLOCKMESH_ID_AIR) && (chunk->blocks[h - 1][15][l].blockID != CFG_BLOCKMESH_ID_AIR))
					{
						chunk->blocks[h][15][l].hide = true;
					}	
				}
			}


			//set in active list
			chunk->isActive = true;
			chunk->locationX = locX;
			chunk->locationY = locY;

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