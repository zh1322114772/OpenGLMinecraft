#include "Render_Vertices.hpp"

namespace renderer
{
	//define block 
	//1-------2
	//|     / |
	//|   /   |
	//3 /_____4

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

	wrapperGL::VAOList<24, 36> Vertices::block;

	void Vertices::cubeGenerator(wrapperGL::VAOList<24, 36>& ref, glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center)
	{
		memcpy(&(ref.vbos), blockPrototypeVBO, 192 * sizeof(float));
		memcpy(&(ref.ebos), blockPrototypeEBO, 36 * sizeof(unsigned int));
		glm::vec3 diff = bottomRight - topLeft;

		for (int i = 0; i < 24; i++)
		{
			wrapperGL::VBO& vbo = ref.vbos[i];
			//set size
			vbo.pos *= diff;
			//set center offset
			vbo.pos -= center;
		}
	}

	void Vertices::load()
	{
		//load block vertices
		cubeGenerator(block, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0));

	}



}