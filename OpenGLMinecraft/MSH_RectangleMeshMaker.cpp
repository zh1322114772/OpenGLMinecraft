#pragma once
#include "MSH_RectangleMeshMaker.hpp"

namespace renderer
{
	namespace mesh
	{
		const float RectangleMeshMaker::rectanglePrototypeVBO[40] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
																	0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
																	1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
																	1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0 };
		const unsigned int RectangleMeshMaker::rectanglePrototypeEBO[6] = { 0, 1, 2, 0, 2, 3 };


		wrapperGL::VAOList* RectangleMeshMaker::makeRectangle(glm::vec2 center, glm::vec2 scale, glm::vec4 frontTexC)
		{
			auto retData = new wrapperGL::VAOList(4, 6);

			memcpy(retData->vbos, rectanglePrototypeVBO, sizeof(wrapperGL::VBO) * 4);
			memcpy(retData->ebos, rectanglePrototypeEBO, sizeof(unsigned int) * 6);

			retData->vbos[0].pos = (retData->vbos[0].pos * glm::vec3(scale, 0.0f)) - glm::vec3(center, 0.0f);
			retData->vbos[0].tex = glm::vec2(frontTexC.x, frontTexC.y);
			retData->vbos[1].pos = (retData->vbos[1].pos * glm::vec3(scale, 0.0f)) - glm::vec3(center, 0.0f);
			retData->vbos[1].tex = glm::vec2(frontTexC.z, frontTexC.y);
			retData->vbos[2].pos = (retData->vbos[2].pos * glm::vec3(scale, 0.0f)) - glm::vec3(center, 0.0);
			retData->vbos[2].tex = glm::vec2(frontTexC.x, frontTexC.w);
			retData->vbos[3].pos = (retData->vbos[3].pos * glm::vec3(scale, 0.0f)) - glm::vec3(center, 0.0);
			retData->vbos[3].tex = glm::vec2(frontTexC.z, frontTexC.w);

			return retData;
		}

	}
}