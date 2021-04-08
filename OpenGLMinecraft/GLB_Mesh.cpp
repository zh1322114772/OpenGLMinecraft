#include "GLB_Mesh.hpp"
#include "Render_Vertices.hpp"
#include "GLW_GLWrapper.hpp"
namespace global
{
	namespace resource
	{
		namespace mesh
		{
			std::atomic<unsigned int> MeshMaker::currentProgress;

			wrapperGL::VAOID MeshMaker::list[static_cast<unsigned int>(MeshType::LAST)];

			void MeshMaker::load() 
			{
				//cube
				auto vaoList = renderer::Vertices::cubeGenerator(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0));
				list[static_cast<unsigned int>(MeshType::CUBE)] = GLWrapper::loadVAOS(vaoList);
				delete vaoList;
				currentProgress++;

				//cubes
				vaoList = renderer::Vertices::cubesGenerator(256, glm::vec3(0.0, 0.0, 1.0));
				list[static_cast<unsigned int>(MeshType::CUBES)] = wrapperGL::GLWrapper::loadVAOS(vaoList);
				delete vaoList;
				currentProgress++;

				//water top cubes
				vaoList = renderer::Vertices::cubesGenerator(256, glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 0.8, 1.0));
				list[static_cast<unsigned int>(MeshType::WATER_TOP_CUBES)] = wrapperGL::GLWrapper::loadVAOS(vaoList);
				delete vaoList;
				currentProgress++;
			}

			const wrapperGL::VAOID* MeshMaker::getMesh(MeshType which)
			{
				return &list[static_cast<unsigned int>(which)];
			}

			float MeshMaker::getLoadingProgress() 
			{
				unsigned int temp = currentProgress.load();
				return (float)temp / static_cast<unsigned int>(MeshType::LAST);
			}

			void MeshMaker::init() 
			{
				currentProgress.store(0);
			}

		}
	}
}