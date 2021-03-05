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
		const static float blockPrototypeVBO[192];
		const static unsigned int blockPrototypeEBO[36];

		//rectangle vertices prototype
		const static float rectanglePrototypeVBO[32];
		const static unsigned int rectanglePrototypeEBO[6];

	public:
		//block vertices
		static wrapperGL::VAOList block;

		/// <summary>
		/// generate a VAOList for cube
		/// </summary>
		/// <param name="ref">VAOList reference</param>
		/// <param name="topLeft">top left coordinate</param>
		/// <param name="bottomRight">bottom right coordinate</param>
		/// <param name="center">the center point</param>
		static void cubeGenerator(wrapperGL::VAOList& ref, glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center);

		/// <summary>
		/// generate a VAOList for 2d rectangle
		/// </summary>
		/// <param name="ref">VAOList reference</param>
		/// <param name="topLeft">top left coordinate</param>
		/// <param name="bottomRight">bottom right coordinate</param>
		/// <param name="center">the center point</param>
		static void rectangleGenerator(wrapperGL::VAOList& ref, glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 center);

		/// <summary>
		/// load all vertices
		/// </summary>
		static void load();

	};


}