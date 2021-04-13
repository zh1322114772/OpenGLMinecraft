#pragma once
#include "GLW_Types.hpp"
namespace renderer
{
	namespace mesh
	{
		class RectangleMeshMaker
		{
		private:
			//rectangle vertices prototype
			const static float rectanglePrototypeVBO[40];
			const static unsigned int rectanglePrototypeEBO[6];

		public:
			/// <summary>
			/// make a rectangle mesh
			/// </summary>
			/// <param name="scale">scale width and height</param>
			/// <param name="center">centered at</param>
			/// <param name="frontTexC">texture coordinates</param>
			/// <returns></returns>
			static wrapperGL::VAOList* makeRectangle(glm::vec2 center, glm::vec2 scale = glm::vec2(1.0, 1.0), glm::vec4 frontTexC = glm::vec4(0.0, 0.0, 1.0, 1.0));
		};
	}
}
