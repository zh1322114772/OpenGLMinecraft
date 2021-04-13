#pragma once
#include "MSH_CubeMeshMaker.hpp"

#define FILL_INFO(beginPtr, texC, scale, center) beginPtr[0].tex = glm::vec2(texC.x, texC.y); \
												beginPtr[0].pos = (beginPtr[0].pos * scale) - center;\
												beginPtr[1].tex = glm::vec2(texC.z, texC.y); \
												beginPtr[1].pos = (beginPtr[1].pos * scale) - center;\
												beginPtr[2].tex = glm::vec2(texC.x, texC.w); \
												beginPtr[2].pos = (beginPtr[2].pos * scale) - center;\
												beginPtr[3].tex = glm::vec2(texC.z, texC.w);\
												beginPtr[3].pos = (beginPtr[3].pos * scale) - center; 

namespace renderer
{
	namespace mesh
	{
		const float CubeMeshMaker::blockPrototypeVBO[240] = { 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
											 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0,
											 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
											 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0,

											 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
											 0.0, 1.0, 1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0,
											 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0,
											 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0,

											 1.0, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 2.0, 0.0,
											 0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 1.0, 0.0, 2.0, 0.0,
											 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 2.0, 0.0,
											 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0, 1.0, 2.0, 0.0,

											 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0,
											 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 3.0, 0.0,
											 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 3.0, 0.0,
											 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 3.0, 0.0,

											 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 4.0, 0.0,
											 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 4.0, 0.0,
											 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 4.0, 0.0,
											 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 4.0, 0.0,

											 0.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 5.0, 0.0,
											 1.0, 0.0, 1.0, 0.0, -1.0, 0.0, 1.0, 0.0, 5.0, 0.0,
											 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 1.0, 5.0, 0.0,
											 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 1.0, 5.0, 0.0 };

		const unsigned int CubeMeshMaker::blockPrototypeEBO[36] = { 0, 1, 2, 1, 3, 2,
													4, 5, 6, 5, 7, 6,
													8, 9, 10, 9, 11, 10,
													12, 13, 14, 13, 15, 14,
													16, 17, 18, 17, 19, 18,
													20, 21, 22, 21, 23, 22 };

		wrapperGL::VAOList* CubeMeshMaker::makeCube( glm::vec3 center, glm::vec3 scale, glm::vec4 frontTexC, glm::vec4 leftTexC, glm::vec4 backTexC, glm::vec4 rightTexC, glm::vec4 upTexC, glm::vec4 downTexC)
		{
			int vboArrByteSize = sizeof(blockPrototypeVBO);
			int eboArrByteSize = sizeof(blockPrototypeEBO);
			int vboUnitSize = sizeof(wrapperGL::VBO);
			int eboUnitSize = sizeof(unsigned int);

			wrapperGL::VAOList* retData = new wrapperGL::VAOList(vboArrByteSize / vboUnitSize, eboArrByteSize / eboUnitSize);

			//copy data from prototype
			memcpy(retData->vbos, blockPrototypeVBO, vboArrByteSize);
			memcpy(retData->ebos, blockPrototypeEBO, eboArrByteSize);

			auto begin = retData->vbos;
			FILL_INFO(begin, frontTexC, scale, center);
			begin += 4;
			FILL_INFO(begin, leftTexC, scale, center);
			begin += 4;
			FILL_INFO(begin, backTexC, scale, center);
			begin += 4;
			FILL_INFO(begin, rightTexC, scale, center);
			begin += 4;
			FILL_INFO(begin, upTexC, scale, center);
			begin += 4;
			FILL_INFO(begin, downTexC, scale, center);

			return retData;
		}

		wrapperGL::VAOList* CubeMeshMaker::makeCube(int s, glm::vec3 center, glm::vec3 scale, glm::vec4 frontTexC, glm::vec4 leftTexC, glm::vec4 backTexC, glm::vec4 rightTexC, glm::vec4 upTexC, glm::vec4 downTexC)
		{
			auto vao = makeCube(center, scale, frontTexC, leftTexC, backTexC, rightTexC, upTexC, downTexC);
			wrapperGL::VAOList** arr = new wrapperGL::VAOList*[s];
			for (int i = 0; i < s; i++) 
			{
				arr[i] = vao;
			}
			auto retData = mergeCubes(arr, s);
			delete[] arr;
			delete vao;

			return retData;
		}

		wrapperGL::VAOList* CubeMeshMaker::mergeCubes(wrapperGL::VAOList** arr, int size) 
		{
			int blockCounter = 0;

			int totalVboSize = 0;
			int totalEboSize = 0;
			int vboUnitSize = sizeof(wrapperGL::VBO);
			int eboUnitSize = sizeof(unsigned int);

			for (int i = 0; i < size; i++)
			{
				wrapperGL::VAOList* currentMesh = arr[i];
				totalVboSize += currentMesh->vboLength;
				totalEboSize += currentMesh->eboLength;
			}

			wrapperGL::VAOList* retData = new wrapperGL::VAOList(totalVboSize, totalEboSize);
			auto vboBegin = retData->vbos;
			auto eboBegin = retData->ebos;

			for (int i = 0; i < size; i++) 
			{
				wrapperGL::VAOList* currentMesh = arr[i];
				memcpy(vboBegin, arr[i]->vbos, arr[i]->vboLength * vboUnitSize);
				memcpy(eboBegin, arr[i]->ebos, arr[i]->eboLength * eboUnitSize);
				
				//get numbers of block in a single mesh
				int blkQ = arr[i]->vboLength / 24;
				for (int j = 0; j < blkQ; j++) 
				{
					auto vboBeginOffset = vboBegin + (j * 24);
					auto eboBeginOffset = eboBegin + (j * 36);

					//assign counter number to every block
					for (int k = 0; k < 24; k++) 
					{
						(vboBeginOffset + k)->extra = blockCounter;
					}

					//correct ebo index to every block
					for (int k = 0; k < 36; k++) 
					{
						*(eboBeginOffset + k) = *(eboBeginOffset + k) + (24 * blockCounter);
					}

					blockCounter++;
				}

				//go next mesh position
				vboBegin += arr[i]->vboLength;
				eboBegin += arr[i]->eboLength;
			}

			return retData;
		}

	}
}