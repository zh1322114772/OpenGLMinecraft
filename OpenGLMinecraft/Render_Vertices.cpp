#include "Render_Vertices.hpp"
#include <stdexcept>
namespace renderer
{

	const float Vertices::rectanglePrototypeVBO[32] = { 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
													   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
														1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
														1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0 };

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

	wrapperGL::VAOList Vertices::block(24, 36);

	void Vertices::rectangleGenerator(wrapperGL::VAOList& ref, glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 center) 
	{
		if (ref.eboLength != 6 || ref.vboLength != 4)
		{
			throw std::runtime_error("EBO and VBO size incorrect");
		}

		memcpy(ref.vbos, rectanglePrototypeVBO, 32 * sizeof(float));
		memcpy(ref.ebos, rectanglePrototypeEBO, 6 * sizeof(unsigned int));
		glm::vec3 diff = glm::vec3(bottomRight - topLeft, 0.0);
		glm::vec3 center_vec3 = glm::vec3(center, 0.0f);
		for (int i = 0; i < 4; i++)
		{
			wrapperGL::VBO& vbo = ref.vbos[i];
			//set size
			vbo.pos *= diff;
			//set center offset
			vbo.pos -= center_vec3;
		}
	
	}

	void Vertices::cubeGenerator(wrapperGL::VAOList& ref, glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center)
	{
		if (ref.eboLength != 36 || ref.vboLength != 24) 
		{
			throw std::runtime_error("EBO and VBO size incorrect");
		}

		memcpy(ref.vbos, blockPrototypeVBO, 192 * sizeof(float));
		memcpy(ref.ebos, blockPrototypeEBO, 36 * sizeof(unsigned int));
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