#pragma once
#include "GLW_Types.hpp"
namespace renderer
{
	/// <summary>
	/// this class contain all vertices for rendering
	/// </summary>
	class Vertices
	{
	private:
		//block vertices prototype
		const static float blockPrototypeVBO[216];
		const static unsigned int blockPrototypeEBO[36];

		//rectangle vertices prototype
		const static float rectanglePrototypeVBO[36];
		const static unsigned int rectanglePrototypeEBO[6];

		/// <summary>
		/// generate a VAOList object based on prototype-vbo and prototype-ebo
		/// </summary>
		/// <param name="protoVbo">prototype vbo</param>
		/// <param name="protoEbo">prototype ebo</param>
		/// <param name="vboSize">vbo array length</param>
		/// <param name="eboSize">ebo array length</param>
		/// <param name="ref">VAOList reference</param>
		/// <param name="topLeft">top left coordinate</param>
		/// <param name="bottomRight">bottom right coordinate</param>
		/// <param name="center">center offset</param>
		/// <returns>VAOList object</returns>
		static wrapperGL::VAOList* objectGenerator(const float* protoVbo, const unsigned int* protoEbo , int vboSize, int eboSize, glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center);

	public:

		/// <summary>
		/// generate a VAOList for cube
		/// </summary>
		/// <param name="topLeft">top left coordinate</param>
		/// <param name="bottomRight">bottom right coordinate</param>
		/// <param name="center">the center point</param>
		/// <returns>VAOList object</returns>
		static wrapperGL::VAOList* cubeGenerator(glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center);

		/// <summary>
		/// generate a VAOList for 2d rectangle
		/// </summary>
		/// <param name="ref">VAOList reference</param>
		/// <param name="topLeft">top left coordinate</param>
		/// <param name="bottomRight">bottom right coordinate</param>
		/// <returns>VAOList object</returns>
		static wrapperGL::VAOList* rectangleGenerator(glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 center);

	};


}