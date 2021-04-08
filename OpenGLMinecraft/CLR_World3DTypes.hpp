#pragma once
#include "GLW_GlmHeaders.hpp"

namespace renderer
{
	namespace controllers
	{
		namespace world3DTypes
		{
			/// <summary>
			/// 3d Polygon object
			/// </summary>
			struct Mesh
			{

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


				Camera(glm::vec3 pos)
				{
					Pos = pos;
					up = glm::vec3(0.0, 1.0, 0.0);
					lookAt = glm::vec3(0.0, 0.0, 0.0);
				};

				Camera()
				{
					Pos = glm::vec3(0.0, 0.0, 0.0);
					up = glm::vec3(0.0, 1.0, 0.0);
					lookAt = glm::vec3(0.0, 0.0, 0.0);
				};

			};
		}
	}
}