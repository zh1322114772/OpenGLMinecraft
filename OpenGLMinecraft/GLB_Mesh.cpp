#include "GLB_Mesh.hpp"
#include "MSH_CubeMeshMaker.hpp"
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
				auto vaoList = renderer::mesh::CubeMeshMaker::makeCube(glm::vec3(0.0));
				list[static_cast<unsigned int>(MeshType::CUBE)] = GLWrapper::loadVAOS(vaoList);
				delete vaoList;
				currentProgress++;

				//cubes
				vaoList = renderer::mesh::CubeMeshMaker::makeCube(256, glm::vec3(0.0, 0.0, 1.0));
				list[static_cast<unsigned int>(MeshType::CUBES)] = wrapperGL::GLWrapper::loadVAOS(vaoList);
				delete vaoList;
				currentProgress++;

				//water top cubes
				vaoList = renderer::mesh::CubeMeshMaker::makeCube(256, glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 0.8, 1.0));
				list[static_cast<unsigned int>(MeshType::WATER_TOP_CUBES)] = wrapperGL::GLWrapper::loadVAOS(vaoList);
				delete vaoList;
				currentProgress++;

				//human
				auto body = renderer::mesh::CubeMeshMaker::makeCube(glm::vec3(0.25, 0.25, 0.125), glm::vec3(0.5, 0.5, 0.25));
				auto armLeft = renderer::mesh::CubeMeshMaker::makeCube(glm::vec3(0.25, 0.6, 0.125), glm::vec3(0.25, 0.6, 0.25));
				auto armRight = renderer::mesh::CubeMeshMaker::makeCube(glm::vec3(0.0, 0.6, 0.125), glm::vec3(0.25, 0.6, 0.25));
				auto head = renderer::mesh::CubeMeshMaker::makeCube(glm::vec3(0.2, 0.0, 0.125), glm::vec3(0.4, 0.3, 0.25));
				auto leg = renderer::mesh::CubeMeshMaker::makeCube(glm::vec3(0.125, 0.7, 0.125), glm::vec3(0.25, 0.7, 0.25));

				wrapperGL::VAOList* mergeList[64];
				int count = 6;
				mergeList[0] = body;
				mergeList[1] = armLeft;
				mergeList[2] = armRight;
				mergeList[3] = head;
				mergeList[4] = leg;
				mergeList[5] = leg;
				vaoList = renderer::mesh::CubeMeshMaker::mergeCubes(mergeList, count);

				list[static_cast<unsigned int>(MeshType::HUMAN)] = wrapperGL::GLWrapper::loadVAOS(vaoList);

				delete vaoList;
				delete body;
				delete armLeft;
				delete armRight;
				delete head;
				delete leg;
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