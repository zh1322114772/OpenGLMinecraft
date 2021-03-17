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
			chunkBuffers = new outputGetterTypes::ChunkBuffer[(int)(powf((viewDistance), 2) * PI)];
		}

		void OutputGetter::onEnable() 
		{
		
		}

		void OutputGetter::onDisable() 
		{
		
		}

		int OutputGetter::getChunkBufferSize() 
		{
			return chunkActiveCount;
		}

		outputGetterTypes::ChunkBuffer* OutputGetter::getChunkBuffer()
		{
			return chunkBuffers;
		}

		void OutputGetter::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			//process chunk data
			auto chunkList = ((ChunkLoader*)taskList[1])->getActiveList();
			
			for (int i = 0; i < chunkList.size(); i++) 
			{
				chunkBuffers[i].locationX = chunkList[i]->locationX;
				chunkBuffers[i].locationY = chunkList[i]->locationY;

				for (int y = 0; y < 256; y++) 
				{
					int visibleCount = 0;
					int invisibleCount = 255;

					for (int x = 0; x < 16; x++) 
					{
						for (int z = 0; z < 16; z++) 
						{

							if (chunkList[i]->blockVisible[y][x][z]) 
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
								data += (unsigned long long)(game::config::resource::BlockMeshIDs::IDList[chunkList[i]->blocks[y][x][z].blockID]->textureID) << 32;

								chunkBuffers[i].info[y][visibleCount] = data;
								visibleCount++;
							}
							else 
							{
								//block invisible
								chunkBuffers[i].info[y][invisibleCount] = 0;
								invisibleCount--;
							}

						}
					}
				}

			}
			chunkActiveCount = chunkList.size();

		}


	}

}