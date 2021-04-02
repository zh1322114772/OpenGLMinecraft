#include "TKB_OutputGetter.hpp"
#include "TKB_ChunkLoader.hpp"
#include "CLR_World3DTypes.hpp"
#include <iostream>
#include <math.h>
#define PI 3.1415926

namespace tickerable
{
	namespace tasks
	{
		namespace outputGetterTypes 
		{
		
		
		
		}



		OutputGetter::OutputGetter(const int viewDistance) 
		{
			chunkBufferSize = (int)(powf((viewDistance), 2) * PI);

			chunkBuffers = new outputGetterTypes::ChunkBuffer* [chunkBufferSize];
			for (int i = 0; i < chunkBufferSize; i++) 
			{
				chunkBuffers[i] = new outputGetterTypes::ChunkBuffer;
			}

		}

		void OutputGetter::onEnable() 
		{
		
		}

		void OutputGetter::onDisable() 
		{
			
		}

		void OutputGetter::onExit() 
		{
			for (int i = 0; i < chunkBufferSize; i++) 
			{
				delete chunkBuffers[i];
			}
			delete[] chunkBuffers;
		}

		int OutputGetter::getChunkBufferSize() 
		{
			return chunkBufferSize;
		}

		outputGetterTypes::ChunkBuffer** OutputGetter::getChunkBuffers()
		{
			return chunkBuffers;
		}

		void OutputGetter::chunkData2ChunkBuffer(outputGetterTypes::ChunkBuffer* chunkBuffer, tasks::chunkLoaderTypes::Chunk* chunkData) 
		{
			chunkBuffer->locationX = chunkData->locationX;
			chunkBuffer->locationY = chunkData->locationY;
			chunkBuffer->updateTime = chunkData->updateTime;
			unsigned short int endIndex[CFG_BLOCKMESH_ID_LAST];


			//set end index
			memcpy(endIndex, chunkData->blockCounter, sizeof(unsigned short int) * CFG_BLOCKMESH_ID_LAST);
			memcpy(chunkBuffer->blockCounter, chunkData->blockCounter, sizeof(unsigned short int) * CFG_BLOCKMESH_ID_LAST);
			
			endIndex[0] -= 1;

			for (int i = 1; i < CFG_BLOCKMESH_ID_LAST; i++)
			{
				endIndex[i] = endIndex[i] + endIndex[i - 1];
			}

			//set block sequence data
			for (unsigned short int y = 0; y < 256; y++) 
			{
				for (unsigned char x = 0; x < 16; x++) 
				{
					for (unsigned char z = 0; z < 16; z++) 
					{
						//if block is visible, then add it to block sequence
						if (chunkData->blockVisibleState[y][x][z] != 0b111111)
						{
							outputGetterTypes::BlockInfo data;
							data.posData.axisX = x;
							data.posData.axisZ = z;
							data.posData.axisY = y;
							data.posData.invisibleFaces = chunkData->blockVisibleState[y][x][z];

							chunkBuffer->blockSequence[endIndex[chunkData->blocks[y][x][z].blockID]] = data;
							endIndex[chunkData->blocks[y][x][z].blockID]--;
						}
					}
				}
			}

			chunkBuffer->isActive = chunkData->isActive;
		}

		void OutputGetter::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			
			//process chunk data
			auto chunkList = ((ChunkLoader*)taskList[1])->getChunkList();

			for (int i = 0; i < chunkBufferSize; i++)
			{

				if ((chunkBuffers[i]->updateTime != chunkList[i]->updateTime))
				{
					if (chunkList[i]->isActive) 
					{
						chunkData2ChunkBuffer(chunkBuffers[i], chunkList[i]);
					}
					else 
					{
						chunkBuffers[i]->isActive = chunkList[i]->isActive;
					}
				}

			}
			

		}


	}

}