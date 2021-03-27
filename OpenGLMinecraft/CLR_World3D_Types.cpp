#include "CLR_World3D_Types.hpp"
#include "GLW_GlmHeaders.hpp"
#include <stdexcept>

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

			BlockMesh::BlockMesh(unsigned int tid, unsigned int nid, unsigned int osid):textureID(tid), normalID(nid), OSID(osid)
			{

			}

			BlockMesh::BlockMesh(unsigned int tid, unsigned int nid, unsigned int osid, unsigned char t) : visible(t), textureID(tid), normalID(nid), OSID(osid)
			{

			}
		}
	}

}
