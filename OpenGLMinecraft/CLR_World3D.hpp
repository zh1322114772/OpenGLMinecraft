#pragma once

#include "Render_Types.hpp"
#include "GLW_GLShader.hpp"
#include "CLR_World3D_Types.hpp"
#include "GLW_Types.hpp"
#include <memory>
#include <iostream>
namespace renderer
{

	namespace controllers
	{

		class World3D : public Controller
		{
		private:
			//current shader program
			std::shared_ptr<wrapperGL::ShaderProgram> shader;

			//view
			glm::mat4 projectionMatrix;
			world3D::Camera camera;
			glm::vec2 mousePos;
			

			//test purpose
			wrapperGL::ImageObject img;
			wrapperGL::TextureID img_v;
			wrapperGL::VAOID block_id;

		public:
			World3D()
			{
				

			}
			
			/// <summary>
			/// set current camera
			/// </summary>
			/// <param name="cam">camera object</param>
			void setCamera(world3D::Camera& cam);

			/// <summary>
			/// set new projection matrix
			/// </summary>
			/// <param name="projection">projection matrix</param>
			void setProjection(glm::mat4& projection);

			//inherited from Controller

			void onStart() override;

			void onExit() override;

			void onEnable() override;

			void onDisable() override;

			void onDraw(const double& delta_t) override;

			void renderAreaChangedCallback(const int& newWidth, const int& newHeight) override;

			void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) override;

		};

	}
}