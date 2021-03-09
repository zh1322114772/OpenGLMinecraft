#pragma once
#include "CLR_Loading.hpp"
#include "GLW_GLWrapper.hpp"
#include "GLSL_Code.hpp"
#include "Render_Vertices.hpp"
#include <iostream>
#include "CFG_Resources.hpp"
#include "Renderer.hpp"
#include "CFG_ControllerIDs.hpp"

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
			shader = new wrapperGL::ShaderProgram(GLSL::LoadingShaderCode, GLSL::LoadingFragmentCode);

			//set vertices
			backgroundV = renderer::Vertices::rectangleGenerator(glm::vec2(0.0, 0.0), glm::vec2(2.0, 2.0), glm::vec2(1.0, 1.0));

			//set image
			backgroundImg = wrapperGL::GLWrapper::loadImage("data\\textures\\Loading.png");

			//load vertices and image to vram
			backgroundImgID = wrapperGL::GLWrapper::loadTexture(backgroundImg);
			backgroundVID = wrapperGL::GLWrapper::loadVAOS(backgroundV);

			progress = 0;

			//set texture loader progress to zero
			textureLoaderProgress = 0;
			textureLoaderProgressI = 0;

			//set vertices loader progress to zero
			verticesLoaderProgress = 0;

			//set blockmesh loader progress to zero
			meshBlockLoaderProgress = 0;

		}

		void Loading::onExit()
		{
			//free memeory
			delete shader;
			delete backgroundV;
			delete backgroundImg;
		}

		void Loading::onEnable() 
		{
		
		}

		void Loading::onDisable()
		{
		
		}

		void Loading::textureLoader() 
		{
			if (textureLoaderProgressI < CFG_TEXTURE_ID_LAST) 
			{
				//more textures need to be loaded
				wrapperGL::ImageObject* imgObj = wrapperGL::GLWrapper::loadImage(game::config::resource::TextureFileNameList::getName((CFG_TEXTURE_ID)textureLoaderProgressI).c_str());
				game::config::resource::TextureIDs::IDList[textureLoaderProgressI] = wrapperGL::GLWrapper::loadTexture(imgObj);
				
				//free imgObj
				delete imgObj;

				//set texture loading progress
				textureLoaderProgressI++;
				textureLoaderProgress = (float)textureLoaderProgressI / CFG_TEXTURE_ID_LAST;
			}

		}

		void Loading::verticesLoader()
		{
			//check if textureloader is completed
			if (textureLoaderProgress < 1.0) return;

			//load all vertices
			game::config::resource::VAOObjectList::load();

			verticesLoaderProgress = 1.0;
		}

		void Loading::meshBlockLoader() 
		{
			//check if textureloader is completed
			if (verticesLoaderProgress < 1.0) return;
			
			//load all meshes
			game::config::resource::BlockMeshIDs::load();

			meshBlockLoaderProgress = 1.0;
			
		}


		void Loading::onDraw(const double& delta_t) 
		{
			//loading tasks
			textureLoader();
			verticesLoader();
			meshBlockLoader();

			//adjust weight for total progress
			progress = (textureLoaderProgress * 0.5) + (verticesLoaderProgress * 0.25) + (meshBlockLoaderProgress * 0.25);
			
			//draw content
			shader->use();
			glClear(GL_COLOR_BUFFER_BIT);
			wrapperGL::GLWrapper::activateTexture(shader, backgroundImgID, "fTexture", GL_TEXTURE0);
			shader->setFloat("progress", progress);
			wrapperGL::GLWrapper::draw(backgroundVID);

			//check if all tasks are loaded, if yes then switch controller
			if (progress >= 1.0) 
			{
				renderer::Easy3D::setContorller(game::config::ControllerIDs::World3D);
			}
		}

		void Loading::renderAreaChangedCallback(const int& newWidth, const int& newHeight) 
		{
		
		}

		void Loading::inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) 
		{
		
		}


		

	}

}