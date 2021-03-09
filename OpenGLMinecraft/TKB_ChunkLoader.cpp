#include "TKB_ChunkLoader.hpp"
#include "TKB_InputGetter.hpp"
#include <iostream>

#define PI 3.1415926
#include "math.h"
namespace tickerable
{
	namespace tasks
	{

		ChunkLoader::ChunkLoader(const int v) : viewDistance(v) 
		{
			chunkListSize = (int)(std::pow((viewDistance + 1), 2) * PI);
			chunkList = new chunkLoaderTypes::Chunk* [chunkListSize];

			//assign space for chunks
			for (int i = 0; i < chunkListSize; i++)
			{
				chunkList[i] = new chunkLoaderTypes::Chunk();
				recycleList.push(chunkList[i]);
			}

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

			//compute current chunk
			long long chunkX = floor(position.x / 16);
			long long chunkY = floor(position.z / 16);

			//clear region mask
			memset(chunkRegionMask, false, sizeof(bool) * 129 * 129);


			std::cout << position.x << " " << position.y << " " << position.z << " " << floor(position.x) << " " << floor(position.z) << std::endl;

			

		}
		
		void ChunkLoader::genChunkData(chunkLoaderTypes::Chunk* chunk, long long locX, long long locY) 
		{
			chunk->isLoading = true;
			chunk->locationX = locX;
			chunk->locationY = locY;


			chunk->isLoading = false;
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