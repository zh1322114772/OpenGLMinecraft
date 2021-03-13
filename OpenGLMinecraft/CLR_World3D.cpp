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
			
			camera = world3D::Camera(glm::vec3(8.0, 5.0, 8.0));

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

		void World3D::blockDrawer(renderer::controllers::world3D::BlockMesh* m) 
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m->textureID);

			wrapperGL::GLWrapper::draw(game::config::resource::VAOObjectList::cubes);
		}

		void World3D::chunkDrawer(tickerable::tasks::chunkLoaderTypes::Chunk* chunk) 
		{
			auto chunkLoc = glm::mat4(1.0);
			auto blockLoc = glm::mat4(1.0);
			//if chunk is in recycle list, then just skip
			if (!chunk->isActive) return;

			for (int y = 0; y < 256; y++)
			{
				//if slice is empty then skip it
				if (!chunk->hideSlice[y]) 
				{
					for (int x = 0; x < 16; x++)
					{
						//if strip is empty then skip it
						if (!chunk->hideStrip[y][x])
						{
							blockLoc = glm::translate(glm::mat4(1.0), glm::vec3((chunk->locationX * 16) + (float)x, (float)y, (chunk->locationY * 16)));
							shader->setMat4("modelMat[0]", blockLoc);
							blockDrawer(game::config::resource::BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_DIRT]);
						}
					}
				}
			}
		
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
				chunkDrawer(chunkList[i]);
			}
		
		}

		void World3D::onDraw(const double& delta_t)
		{
			shader->use();

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

			//set input to world tick clock
			tickClock->getInputGetter()->setPosition(camera.Pos.x, camera.Pos.y, camera.Pos.z);
			tickClock->getInputGetter()->setView(camera.lookAt);
		}
	}

}