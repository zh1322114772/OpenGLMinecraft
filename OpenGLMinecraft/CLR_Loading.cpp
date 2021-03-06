#pragma once
#include "CLR_Loading.hpp"
#include "GLW_GLWrapper.hpp"
#include "GLSL_Code.hpp"
#include "Render_Vertices.hpp"
#include <iostream>
namespace renderer
{

	namespace controllers
	{
		Loading::Loading()
		{

		}

		void Loading::onStart()
		{
			//load shader
			wrapperGL::ShaderProgram shader = wrapperGL::ShaderProgram(GLSL::LoadingShaderCode, GLSL::LoadingFragmentCode);

			//set vertices
			backgroundV = renderer::Vertices::rectangleGenerator(glm::vec2(0.0, 0.0), glm::vec2(2.0, 2.0), glm::vec2(0.5, 0.5));

			//set image
			backgroundImg = wrapperGL::GLWrapper::loadImage("data\\textures\\Loading.png");

			//load vertices and image to vram
			backgroundImgID = wrapperGL::GLWrapper::loadTexture(backgroundImg);
			backgroundVID = wrapperGL::GLWrapper::loadVAOS(*backgroundV);

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
			shader.use();

			glClear(GL_COLOR_BUFFER_BIT);

			wrapperGL::GLWrapper::activateTexture(&shader, backgroundImgID, "fTexture", GL_TEXTURE0);

			wrapperGL::GLWrapper::draw(backgroundVID);
		}

		void Loading::renderAreaChangedCallback(const int& newWidth, const int& newHeight) 
		{
		
		}

		void Loading::inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) 
		{
		
		}


		

	}

}