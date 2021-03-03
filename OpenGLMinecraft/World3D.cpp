#include "World3D.hpp"
#include "GLSL_Code.hpp"
namespace renderer
{
	namespace controllers
	{
		void World3D::onStart()
		{
			shader = std::shared_ptr<wrapperGL::ShaderProgram>(new wrapperGL::ShaderProgram(GLSL::vertexShaderCode, GLSL::blockRenderFragmentCode));
			shader = nullptr;
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


		}

		void  World3D::renderAreaChangedCallback(const int& newWidth, const int& newHeight)
		{

		}

		void  World3D::inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent)
		{


		}
	}

}