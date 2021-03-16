#include "CLR_World3D.hpp"

#include "GLSL_Code.hpp"
#include "GLW_GLWrapper.hpp"
#include "Renderer.hpp"
#include "CFG_Resources.hpp"

namespace renderer
{
	namespace controllers
	{
		World3D::World3D(tickerable::WorldTickClock* clock)
		{
			tickClock = clock;
		}


		void World3D::onStart()
		{
			shader = std::shared_ptr<wrapperGL::ShaderProgram>(new wrapperGL::ShaderProgram(GLSL::World3DvertexShaderCode, GLSL::World3DWorldFragmentCode));

			//set camera and projection matrix
			projectionMatrix = glm::perspective(glm::radians(45.0f), (float)renderer::Easy3D::getRenderAreaWidth() / renderer::Easy3D::getRenderAreaHeight(), 0.5f, 200.f);
			renderer::Easy3D::setMouseCenter(true);
			
			camera = world3D::Camera(glm::vec3(0.0, 20.0, 0.0));

			mousePos.x = -1.57;
			mousePos.y = 0.0;

			//load block
			blockV = Vertices::cubeGenerator(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0));

			blockVID = wrapperGL::GLWrapper::loadVAOS(blockV);

			//init clock clock
			tickClock->start();
			tickClock->pause();
		}



		void World3D::setCamera(world3D::Camera& cam) 
		{
			camera = cam;
		}

		void World3D::setProjection(glm::mat4& projection) 
		{
			projectionMatrix = projection;
		}

		void World3D::onExit()
		{
			tickClock->stop();
		}

		void World3D::onEnable()
		{
			//enable depth test
			glEnable(GL_DEPTH_TEST);

			tickClock->resume();
		}

		void World3D::onDisable()
		{
			//enable depth test
			glDisable(GL_DEPTH_TEST);

			tickClock->pause();
		}

		void World3D::blockDrawer(game::config::blocks::Block block) 
		{
			//active textures
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, game::config::resource::BlockMeshIDs::IDList[block.blockID]->textureID);

			wrapperGL::GLWrapper::draw(game::config::resource::VAOObjectList::cube);
		}

		void World3D::chunkDrawer(tickerable::tasks::chunkLoaderTypes::Chunk* chunk) 
		{

			for (int y = 0; y < 256; y++) 
			{
				for (int x = 0; x < 16; x++) 
				{
					for (int z = 0; z < 16; z++) 
					{
						if (game::config::resource::BlockMeshIDs::IDList[chunk->blocks[y][x][z].blockID]->visible == renderer::controllers::world3D::BlockMesh::VISIBLE) 
						{
							auto offset = glm::translate(glm::mat4(1.0), glm::vec3((chunk->locationX * 16) + (float)x, (float)y, (chunk->locationY * 16) + (float)z));
							shader->setMat4("modelMat[0]", offset);
							blockDrawer(chunk->blocks[y][x][z]);
						}
					
					}
				}
			}

			/***
			auto chunkLoc = glm::mat4(1.0);
			auto blockLoc = glm::mat4(1.0);
			//if chunk is in recycle list, then just skip
			if (!chunk->isActive) return;

			for (int y = 0; y < 256; y++)
			{
				unsigned short int sliceVisible = chunk->sliceVisible[y];

				//if 1*16*16 area has visible block
				if (sliceVisible)
				{
					for (int x = 0; x < 16; x++)
					{
						bool sliceVisibleCmpBit = sliceVisible & 0b1;
						sliceVisible >>= 1;

						//if 1*1*16 area has visible block
						if (sliceVisibleCmpBit)
						{
							blockLoc = glm::translate(glm::mat4(1.0), glm::vec3((chunk->locationX * 16) + (float)x, (float)y, (chunk->locationY * 16)));
							shader->setMat4("modelMat[0]", blockLoc);
							shader->setUInt("isBlockVisible", chunk->visibleState[y][x]);
							blockDrawer(chunk->blocks[y][x]);
						}
					}
				}
			}
			*/
		}

		void World3D::terrainDrawer() 
		{
			//bind textures
			shader->setInt("fTexture", 0);

			auto chunkList = tickClock->getChunkLoader()->getChunkList();
			auto chunkListSize = tickClock->getChunkLoader()->getChunkListSize();
			shader->setInt("modelMatSize", 1);
			for (auto i = 0; i < chunkListSize; i++)
			{
				if (chunkList[i]->isActive) 
				{
					chunkDrawer(chunkList[i]);
				}
				
			}
		
		}

		void World3D::onDraw(const double& delta_t)
		{
			static double testTime = 0;
			testTime += delta_t;

			shader->use();

			//std::cout << sinf(testTime * 0.1) << " " << cosf(testTime * 0.1) << std::endl;

			//test global light
			glm::vec3 lightDirection(0.5, -0.5, 0.5);
			lightDirection = glm::normalize(lightDirection);
			glm::vec3 sunColor(0.7, 0.7, 0.55);
			glm::vec3 sunShadeColor(0.35, 0.35, 0.22);
			glm::vec3 sunSpecular(1.5, 1.5, 1.2);

			shader->setVec3("globalLight.lightDirection", lightDirection);
			shader->setVec3("globalLight.lightColorA", sunShadeColor);
			shader->setVec3("globalLight.lightColorD", sunColor);
			shader->setVec3("globalLight.lightColorS", sunSpecular);
			shader->setVec3("cameraPosition", camera.Pos);

			//set view and projection matrices to vertex shader
			glm::mat4 lookAtMatrix = glm::lookAt(camera.Pos, camera.Pos + camera.lookAt, camera.up);

			shader->setMat4("viewMat", lookAtMatrix);
			shader->setMat4("projectionMat", projectionMatrix);

			//clear 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//draw terrain
			terrainDrawer();

		}

		void  World3D::renderAreaChangedCallback(const int& newWidth, const int& newHeight)
		{

		}

		void  World3D::inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t)
		{
			//std::cout << mouseEvent.mousePosition.x << std::endl;


			mousePos.x += mouseEvent.mousePosition.x / 100;
			mousePos.y += -mouseEvent.mousePosition.y / 100;
			
			if (mousePos.y >= 1.57)
			{
				mousePos.y = 1.57;
			}
			else if (mousePos.y <= -1.57)
			{
				mousePos.y = -1.57;
			}

			//2d xy to xyz
			camera.lookAt.x = cosf(mousePos.x) * cosf(mousePos.y);
			camera.lookAt.y = sinf(mousePos.y);
			camera.lookAt.z = sinf(mousePos.x) * cosf(mousePos.y);

			//change position
			if (keyboardEvent.keyPressed[GLFW_KEY_W]) 
			{
				camera.Pos += camera.lookAt * 5.0f * (float)delta_t;
			}
			
			if (keyboardEvent.keyPressed[GLFW_KEY_S]) 
			{
				camera.Pos -= camera.lookAt * 5.0f * (float)delta_t;
			}

			if (keyboardEvent.keyPressed[GLFW_KEY_A]) 
			{
				camera.Pos -= glm::cross(camera.lookAt, camera.up) * 5.0f * (float)delta_t;
			}

			if (keyboardEvent.keyPressed[GLFW_KEY_D]) 
			{
				camera.Pos += glm::cross(camera.lookAt, camera.up) * 5.0f * (float)delta_t;
			}

			std::cout << camera.Pos.x << " " << camera.Pos.y << " " << camera.Pos.z << std::endl;

			//set input to world tick clock
			tickClock->getInputGetter()->setPosition(camera.Pos.x, camera.Pos.y, camera.Pos.z);
			tickClock->getInputGetter()->setView(camera.lookAt);
		}
	}

}