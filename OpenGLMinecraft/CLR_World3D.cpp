#include "CLR_World3D.hpp"

#include "GLSL_Code.hpp"
#include "GLW_GLWrapper.hpp"
#include "Renderer.hpp"

namespace renderer
{
	namespace controllers
	{
		void World3D::onStart()
		{
			shader = std::shared_ptr<wrapperGL::ShaderProgram>(new wrapperGL::ShaderProgram(GLSL::World3DvertexShaderCode, GLSL::World3DFragmentCode));
			//load textures
			img = wrapperGL::GLWrapper::loadImage("data\\textures\\blocks\\cobblestone.png");
			img_v = wrapperGL::GLWrapper::loadTexture(img);


			//set camera and projection matrix
			projectionMatrix = glm::perspective(glm::radians(45.0f), (float)renderer::Easy3D::getRenderAreaWidth() / renderer::Easy3D::getRenderAreaHeight(), 0.1f, 100.f);
			renderer::Easy3D::setMouseCenter(true);
			
			camera = world3D::Camera(glm::vec3(0.0, 0.0, 0.0));

			mousePos.x = -1.57;
			mousePos.y = 0.0;

			//load block
			blockV = Vertices::cubeGenerator(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0));
			blockVID = wrapperGL::GLWrapper::loadVAOS(*blockV);

			//enable depth test
			glEnable(GL_DEPTH_TEST);
			
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

		}

		void World3D::onEnable()
		{

		}

		void World3D::onDisable()
		{

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

			//draw new content

			wrapperGL::GLWrapper::activateTexture(shader.get(), img_v, "fTexture", GL_TEXTURE0);

			//draw cube
			auto model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0, 0.0, 1.0));
			//model = glm::scale(model, glm::vec3(1.3, 1.3, 1.3));

			shader->setInt("modelMatSize", 1);
			shader->setMat4("modelMat[0]", model);

			wrapperGL::GLWrapper::draw(blockVID);
		}

		void  World3D::renderAreaChangedCallback(const int& newWidth, const int& newHeight)
		{

		}

		void  World3D::inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t)
		{

			mousePos.x += mouseEvent.mousePosition.x * delta_t;
			mousePos.y += -mouseEvent.mousePosition.y * delta_t;
			
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
				camera.Pos += camera.lookAt * (float)delta_t;
			}
			
			if (keyboardEvent.keyPressed[GLFW_KEY_S]) 
			{
				camera.Pos -= camera.lookAt * (float)delta_t;
			}

			if (keyboardEvent.keyPressed[GLFW_KEY_A]) 
			{
				camera.Pos -= glm::cross(camera.lookAt, camera.up) * (float)delta_t;
			}

			if (keyboardEvent.keyPressed[GLFW_KEY_D]) 
			{
				camera.Pos += glm::cross(camera.lookAt, camera.up) * (float)delta_t;
			}

			std::cout << "  X: " << camera.Pos.x << "  Y: " << camera.Pos.y << "  Z: " << camera.Pos.z << std::endl;

		}
	}

}