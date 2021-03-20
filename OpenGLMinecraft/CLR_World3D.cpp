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
			shader = std::shared_ptr<wrapperGL::ShaderProgram>(new wrapperGL::ShaderProgram(GLSL::World3DBlockVertexShaderCode, GLSL::World3DBlockFragmentCode));

			//set camera and projection matrix
			projectionMatrix = glm::perspective(glm::radians(45.0f), (float)renderer::Easy3D::getRenderAreaWidth() / renderer::Easy3D::getRenderAreaHeight(), 0.5f, 1000.f);
			renderer::Easy3D::setMouseCenter(true);
			
			camera = world3D::Camera(glm::vec3(0.0, 150.0, 0.0));

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

		void World3D::terrainDrawer() 
		{
			//set textures
			for (int i = 0; i < 24; i++) 
			{
				shader->setInt("fTexture["+std::to_string(i)+"]", i);
			}

			auto chunkList = tickClock->getOutputGetter()->getChunkBuffers();
			auto chunkListSize = tickClock->getOutputGetter()->getChunkBufferSize();

			//record block position
			float blockPos[72];
			unsigned int blockTex[24];
			int blockCounter = 0;
			
			//iterate through all active chunks
			for (int c = 0; c < chunkListSize; c++)
			{
				auto thisChunk = chunkList[c];
				float thisChunkX = thisChunk->locationX * 16;
				float thisChunkZ = thisChunk->locationY * 16;

				//iterate through single chunk
				for (int y = 0; y < 256; y++)
				{
					//if slice exist visible blocks
					if (!(thisChunk->info[y][0])) continue;

					//iterate through every single block in a slice
					for (int i = 0; i < 256; i++) 
					{
						unsigned long long info = thisChunk->info[y][i];

						//check if reachs to the end
						if (!info) break;
						
						if (blockCounter >= 24) 
						{
							//send position data to gpu
							shader->setFloat("blockPosition", blockPos, 72);

							//bind texture
							for (int k = 0; k < 24; k++)
							{
								glActiveTexture(GL_TEXTURE0 + k);
								glBindTexture(GL_TEXTURE_2D, blockTex[k]);
							}

							wrapperGL::GLWrapper::draw(game::config::resource::VAOObjectList::cubes);
							blockCounter = 0;
						}

						//write block position data
						blockPos[(blockCounter * 3)] = thisChunkX + (float)((info & 0xf0) >> 4);
						blockPos[(blockCounter * 3) + 1] = (float)y;
						blockPos[(blockCounter * 3) + 2] = thisChunkZ + (float)(info & 0xf);

						//write block texture data
						blockTex[blockCounter] = ((info & 0xffffffff00000000) >> 32);

						blockCounter++;
					}

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
				camera.Pos += camera.lookAt * 5.0f * (float)delta_t * 10.0f;
			}
			
			if (keyboardEvent.keyPressed[GLFW_KEY_S]) 
			{
				camera.Pos -= camera.lookAt * 5.0f * (float)delta_t * 10.0f;
			}

			if (keyboardEvent.keyPressed[GLFW_KEY_A]) 
			{
				camera.Pos -= glm::cross(camera.lookAt, camera.up) * 5.0f * (float)delta_t * 10.0f;
			}

			if (keyboardEvent.keyPressed[GLFW_KEY_D]) 
			{
				camera.Pos += glm::cross(camera.lookAt, camera.up) * 5.0f * (float)delta_t * 10.0f;
			}

			//std::cout << camera.Pos.x << " " << camera.Pos.y << " " << camera.Pos.z << std::endl;

			//set input to world tick clock
			tickClock->getInputGetter()->setPosition(camera.Pos.x, camera.Pos.y, camera.Pos.z);
			tickClock->getInputGetter()->setView(camera.lookAt);
		}
	}

}