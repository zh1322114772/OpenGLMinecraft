#include "CLR_World3D_Types.hpp"
#include <glm/glm.hpp>

namespace renderer
{
	namespace controllers
	{
		namespace world3D
		{
			Camera::Camera(glm::vec3 pos)
			{
				Pos = pos;
				up = glm::vec3(0.0, 1.0, 0.0);
				lookAt = glm::vec3(0.0, 0.0, 0.0);
			}

			Camera::Camera()
			{
				Pos = glm::vec3(0.0, 0.0, 0.0);
				up = glm::vec3(0.0, 1.0, 0.0);
				lookAt = glm::vec3(0.0, 0.0, 0.0);
			}

		}
	}

}
