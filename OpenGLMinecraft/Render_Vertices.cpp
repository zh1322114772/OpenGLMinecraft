#include "Render_Vertices.hpp"
#include <stdexcept>

namespace renderer
{

	const float Vertices::rectanglePrototypeVBO[32] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
													   0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
														1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
														1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0 };

	const unsigned int Vertices::rectanglePrototypeEBO[6] = { 0, 1, 2, 0, 2, 3 };

	const float Vertices::blockPrototypeVBO[192] = { 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
											 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0,
											 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0,
											 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0,
											 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0,
											 0.0, 1.0, 1.0, -1.0, 0.0, 0.0, 1.0, 0.0,
											 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0,
											 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, 1.0, 1.0,
											 1.0, 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0,
											 0.0, 1.0, 0.0, 0.0, 0.0, -1.0, 1.0, 0.0,
											 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0,
											 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0, 1.0,
											 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
											 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
											 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0,
											 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
											 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
											 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0,
											 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0,
											 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0,
											 0.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 0.0,
											 1.0, 0.0, 1.0, 0.0, -1.0, 0.0, 1.0, 0.0,
											 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 1.0,
											 1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 1.0 };

	const unsigned int Vertices::blockPrototypeEBO[36] = { 0, 1, 2, 1, 2, 3,
													4, 5, 6, 5, 6, 7,
													8, 9, 10, 9, 10, 11,
													12, 13, 14, 13, 14, 15,
													16, 17, 18, 17, 18, 19,
													20, 21, 22, 21, 22, 23 };

	wrapperGL::VAOList* Vertices::objectGenerator(const float* protoVbo, const unsigned int* protoEbo, int vboSize, int eboSize, glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center) 
	{
		wrapperGL::VAOList* retData = new wrapperGL::VAOList(vboSize / sizeof(wrapperGL::VBO), eboSize / sizeof(unsigned int));

		//copy data from prototype
		memcpy(retData->vbos, protoVbo, vboSize);
		memcpy(retData->ebos, protoEbo, eboSize);

		glm::vec3 diff = bottomRight - topLeft;

		for (int i = 0; i < retData->vboLength; i++)
		{
			wrapperGL::VBO& vbo = retData->vbos[i];

			//set new size
			vbo.pos *= diff;

			//set center offset
			vbo.pos -= center;
		}

		return retData;
	}

	wrapperGL::VAOList* Vertices::rectangleGenerator(glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 center) 
	{

		glm::vec3 topLeftVec3 = glm::vec3(topLeft, 0.0);
		glm::vec3 bottomRightVec3 = glm::vec3(bottomRight, 0.0);
		glm::vec3 venterVec3 = glm::vec3(center, 0.0);

		return objectGenerator(rectanglePrototypeVBO, rectanglePrototypeEBO, sizeof(rectanglePrototypeVBO), sizeof(rectanglePrototypeEBO),topLeftVec3, bottomRightVec3, venterVec3);
	}

	wrapperGL::VAOList* Vertices::cubeGenerator(glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center)
	{
		return objectGenerator(blockPrototypeVBO, blockPrototypeEBO, sizeof(blockPrototypeVBO), sizeof(blockPrototypeEBO),topLeft, bottomRight, center);
	}

}