#pragma once
#include "GLW_GlmHeaders.hpp"
#include "GLW_Types.hpp"
#include <vector>
namespace renderer
{
	namespace controllers
	{
		namespace world3D 
		{

			/// <summary>
			/// 3d Polygon object
			/// </summary>
			struct Mesh 
			{
				
			};

			/// <summary>
			/// 3d block object
			/// </summary>
			struct BlockMesh 
			{

				unsigned int textureID;

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tID">texture id</param>
				/// <returns></returns>
				BlockMesh(wrapperGL::TextureID& tID);
			};

			struct Camera 
			{
				/// <summary>
				/// camera up vector
				/// </summary>
				glm::vec3 up;

				/// <summary>
				/// camera world position
				/// </summary>
				glm::vec3 Pos;

				/// <summary>
				/// camera direction
				/// </summary>
				glm::vec3 lookAt;


				Camera(glm::vec3 pos);

				Camera();

			};
		
		}
	}
}
