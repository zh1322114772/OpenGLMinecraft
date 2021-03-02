#pragma once
#include "WrapperTypes.hpp"
namespace renderer
{
	/// <summary>
	/// this class contain all vertices that's needed for rendering
	/// </summary>
	class Vertices 
	{
	private:
		static float blockPrototypeVBO[192];
		static unsigned int blockPrototypeEBO[36];

	public:
		//block vertices
		static wrapperGL::VAOList<24, 36> block;



		/// <summary>
		/// load all vertices
		/// </summary>
		static void load();
	
	};

}