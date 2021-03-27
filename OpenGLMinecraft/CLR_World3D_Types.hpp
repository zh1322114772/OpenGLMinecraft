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
				static const unsigned char VISIBLE = 0;
				static const unsigned char TRANSPARENT = 1;
				static const unsigned char INVISIBLE = 2;
				static const unsigned char RELFECT = 3;

				/// <summary>
				/// texture id
				/// </summary>
				unsigned int textureID;
				
				/// <summary>
				/// normal map id
				/// </summary>
				unsigned int normalID;

				/// <summary>
				/// specular and occlusion map id
				/// </summary>
				unsigned int OSID;

				unsigned char visible = VISIBLE;

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <returns></returns>
				BlockMesh(unsigned int tid, unsigned int nid, unsigned int osid);
				
				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <param name="t">if texture is transparent</param>
				/// <returns></returns>
				BlockMesh(unsigned int tid, unsigned int nid, unsigned int osid, unsigned char t);
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
