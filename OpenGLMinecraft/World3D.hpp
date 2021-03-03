#pragma once
#include "Render_Types.hpp"
#include "GLW_GLShader.hpp"
#include <memory>
namespace renderer
{
	namespace controllers
	{
		class World3D : public Controller
		{
		private:
			//current shader program
			std::shared_ptr<wrapperGL::ShaderProgram> shader;
		public:
			World3D()
			{


			}

			void onStart() override;

			void onExit() override;

			void onEnable() override;

			void onDisable() override;

			void onDraw(const double& delta_t);

			void renderAreaChangedCallback(const int& newWidth, const int& newHeight);

			void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent);

		};

	}
}