#pragma once
#include <glm/glm.hpp>

namespace renderer
{
	namespace controllers
	{
		namespace world3D 
		{
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
