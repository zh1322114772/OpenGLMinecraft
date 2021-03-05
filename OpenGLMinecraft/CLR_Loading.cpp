#pragma once
#include "CLR_Loading.hpp"
#include "GLW_GLWrapper.hpp"
#include "GLSL_Code.hpp"
#include "Render_Vertices.hpp"
namespace renderer
{

	namespace controllers
	{
		Loading::Loading()
		{
			background = wrapperGL::VAOList(4, 6);
			renderer::Vertices::rectangleGenerator(background, glm::vec2(0.0, 0.0), glm::vec2(2.0, 2.0), glm::vec2(1.0, 1.0));


		}

		void Loading::onStart()
		{
			
		}

		void Loading::onExit()
		{
		
		}

		void Loading::onEnable() 
		{
		
		}

		void Loading::onDisable()
		{
		
		}

		void Loading::onDraw(const double& delta_t) 
		{
		
		}

		void Loading::renderAreaChangedCallback(const int& newWidth, const int& newHeight) 
		{
		
		}

		void Loading::inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) 
		{
		
		}


		

	}

}