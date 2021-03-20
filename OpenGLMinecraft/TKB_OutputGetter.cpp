#include "TKB_OutputGetter.hpp"
#include "TKB_ChunkLoader.hpp"
#include "CLR_World3D_Types.hpp"
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

			chunkBuffersActive = new outputGetterTypes::ChunkBuffer* [chunkBufferSize];
			chunkBuffers = new outputGetterTypes::ChunkBuffer* [chunkBufferSize];
			for (int i = 0; i < chunkBufferSize; i++) 
			{
				chunkBuffers[i] = new outputGetterTypes::ChunkBuffer;
				chunkBuffers[i]->chunkID = i;
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
			delete[] chunkBuffersActive;
		}

		int OutputGetter::getChunkBufferSize() 
		{
			return chunkActiveCount;
		}

		outputGetterTypes::ChunkBuffer** OutputGetter::getChunkBuffers()
		{
			return chunkBuffersActive;
		}

		void OutputGetter::chunkData2ChunkBuffer(outputGetterTypes::ChunkBuffer* chunkBuffer, tasks::chunkLoaderTypes::Chunk* chunkData) 
		{

			chunkBuffer->locationX = chunkData->locationX;
			chunkBuffer->locationY = chunkData->locationY;
			chunkBuffer->timeStamp = chunkData->timeStamp;

			for (int y = 0; y < 256; y++)
			{
				int visibleCount = 0;
				int invisibleCount = 255;

				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{

						if (chunkData->blockVisible[y][x][z])
						{
							//block visible
							unsigned long long data = 0;

							//z axis
							data += z;
							//x axis
							data += (x) << 4;
							//9th bit always 1
							data += 0b100000000;
							//texture id
							data += (unsigned long long)(game::config::resource::BlockMeshIDs::IDList[chunkData->blocks[y][x][z].blockID]->textureID) << 32;

							chunkBuffer->info[y][visibleCount] = data;
							visibleCount++;
						}
						else
						{
							//block invisible
							chunkBuffer->info[y][invisibleCount] = 0;
							invisibleCount--;
						}

					}
				}
			}
		
		
		}

		void OutputGetter::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			
			//process chunk data
			auto chunkList = ((ChunkLoader*)taskList[1])->getActiveList();
			int counter = 0;

			for (int i = 0; i < chunkList.size(); i++)
			{

				auto ChkBfPointer = chunkBuffers[chunkList[i]->chunkID];
				if (ChkBfPointer->timeStamp != chunkList[i]->timeStamp) 
				{
					ChkBfPointer->locationX = chunkList[i]->locationX;
					ChkBfPointer->locationY = chunkList[i]->locationY;
					ChkBfPointer->timeStamp = chunkList[i]->timeStamp;

					chunkData2ChunkBuffer(ChkBfPointer, chunkList[i]);
				}
				chunkBuffersActive[counter] = ChkBfPointer;
				counter++;

			}

			chunkActiveCount = chunkList.size();
			

			/***
			auto chunkList = ((ChunkLoader*)taskList[1])->getActiveList();

			for (int i = 0; i < chunkList.size(); i++)
			{
				
				chunkData2ChunkBuffer(chunkBuffers[i], chunkList[i]);
			}
			chunkActiveCount = chunkList.size();
			*/
		}


	}

}