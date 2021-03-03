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

	public:
		//block vertices
		static wrapperGL::VAOList<24, 36> block;

		/// <summary>
		/// generate a cube
		/// </summary>
		/// <param name="ref">destination</param>
		/// <param name="topLeft">top left coordinate</param>
		/// <param name="bottomRight">bottom right coordinate</param>
		/// <param name="center">the center point of the cube</param>
		static void cubeGenerator(wrapperGL::VAOList<24, 36>& ref, glm::vec3 topLeft, glm::vec3 bottomRight, glm::vec3 center);

		/// <summary>
		/// load all vertices
		/// </summary>
		static void load();

	};

}