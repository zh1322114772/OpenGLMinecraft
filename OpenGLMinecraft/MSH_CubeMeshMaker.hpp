#pragma once
#include "GLW_Types.hpp"
namespace renderer
{
	namespace mesh 
	{
		class CubeMeshMaker 
		{
		private:
			//cube prototype
			const static float blockPrototypeVBO[240];
			const static unsigned int blockPrototypeEBO[36];

		public:
			/// <summary>
			/// make cube mesh
			/// </summary>
			/// <param name="center">where the cube centered at </param>
			/// <param name="scale">scale the cube size, default with szie 1 </param>
			/// <param name="frontTexC">cube front texture coordinates</param>
			/// <param name="leftTexC">cube left texture coordinates</param>
			/// <param name="backTexC">cube back texture coordinates</param>
			/// <param name="rightTexC">cube right texture coordinates</param>
			/// <param name="upTexC">cube up texture coordinates</param>
			/// <param name="downTexC">cube down texture coordinates</param>
			/// <returns></returns>
			static wrapperGL::VAOList* makeCube(glm::vec3 center, glm::vec3 scale = glm::vec3(1.0), glm::vec4 frontTexC = glm::vec4(0.0, 0.0, 1.0, 1.0), 
																																				glm::vec4 leftTexC = glm::vec4(0.0, 0.0, 1.0, 1.0), 
																																				glm::vec4 backTexC = glm::vec4(0.0, 0.0, 1.0, 1.0), 
																																				glm::vec4 rightTexC = glm::vec4(0.0, 0.0, 1.0, 1.0), 
																																				glm::vec4 upTexC = glm::vec4(0.0, 0.0, 1.0, 1.0), 
																																				glm::vec4 downTexC = glm::vec4(0.0, 0.0, 1.0, 1.0));

			/// <summary>
			/// make cubes mesh
			/// </summary>
			/// <param name="s">number of cubes</param>
			/// <param name="center">where the cube centered at </param>
			/// <param name="scale">scale the cube size, default with szie 1 </param>
			/// <param name="frontTexC">cube front texture coordinates</param>
			/// <param name="leftTexC">cube left texture coordinates</param>
			/// <param name="backTexC">cube back texture coordinates</param>
			/// <param name="rightTexC">cube right texture coordinates</param>
			/// <param name="upTexC">cube up texture coordinates</param>
			/// <param name="downTexC">cube down texture coordinates</param>
			/// <returns></returns>
			static wrapperGL::VAOList* makeCube(int s, glm::vec3 center, glm::vec3 scale = glm::vec3(1.0), glm::vec4 frontTexC = glm::vec4(0.0, 0.0, 1.0, 1.0),
																																				glm::vec4 leftTexC = glm::vec4(0.0, 0.0, 1.0, 1.0),
																																				glm::vec4 backTexC = glm::vec4(0.0, 0.0, 1.0, 1.0),
																																				glm::vec4 rightTexC = glm::vec4(0.0, 0.0, 1.0, 1.0),
																																				glm::vec4 upTexC = glm::vec4(0.0, 0.0, 1.0, 1.0),
																																				glm::vec4 downTexC = glm::vec4(0.0, 0.0, 1.0, 1.0));

			/// <summary>
			/// merge multiple vaolist into one
			/// </summary>
			/// <param name="vaolist">vaolist array</param>
			/// <param name="size">array size</param>
			/// <returns></returns>
			static wrapperGL::VAOList* mergeCubes(wrapperGL::VAOList** arr, int size);
		};
	}

}