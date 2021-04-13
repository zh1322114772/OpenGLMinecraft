#pragma once
#include "CLR_Loading.hpp"
#include "GLW_GLWrapper.hpp"
#include "GLSL_Code.hpp"
#include <iostream>
#include "Renderer.hpp"
#include "GLB_ControllerIDs.hpp"
#include "BitMapProcess.hpp"
#include "MSH_RectangleMeshMaker.hpp"
#include <string>
#include <thread>

#include "GLB_Texture.hpp"
#include "GLB_Block.hpp"
#include "GLB_Mesh.hpp"
#include "GLB_Entity.hpp"

using namespace global::resource;

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
			backgroundV = renderer::mesh::RectangleMeshMaker::makeRectangle(glm::vec2(0.0, 0.0));

			//set image
			backgroundImg = wrapperGL::GLWrapper::loadImage("data\\textures\\Loading.png");

			//load vertices and image to vram
			backgroundImgID = wrapperGL::GLWrapper::loadTexture(backgroundImg);
			backgroundVID = wrapperGL::GLWrapper::loadVAOS(backgroundV);

			progress = 0;

			//set texture loader progress to zero
			textureLoaderProgress = 0;

			//set vertices loader progress to zero
			verticesLoaderProgress = 0;

			//set blockmesh loader progress to zero
			meshBlockLoaderProgress = 0;


			texture::TextureMaker::init();
			global::resource::mesh::MeshMaker::init();
			block::BlockRenderInfoMaker::init();
			entity::EntityRenderInfoMaker::init();

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
			texture::TextureMaker::load();
			textureLoaderProgress = 1.0;
		}

		void Loading::verticesLoader()
		{
			//check if textureloader is completed
			if (textureLoaderProgress < 1.0) return;

			global::resource::mesh::MeshMaker::load();
			verticesLoaderProgress = 1.0;
		}

		void Loading::blockLoader() 
		{
			block::BlockRenderInfoMaker::load();

			//test
			entity::EntityRenderInfoMaker::load();

			meshBlockLoaderProgress = 1.0;
		}


		void Loading::onDraw(const double& delta_t) 
		{
			//loading tasks
			textureLoader();
			verticesLoader();
			blockLoader();

			//adjust weight for total progress
			progress = (textureLoaderProgress * 0.5) + (verticesLoaderProgress * 0.25) + (meshBlockLoaderProgress * 0.25);
			
			//draw content
			shader->use();
			glClear(GL_COLOR_BUFFER_BIT);
			wrapperGL::GLWrapper::activateTexture(shader, backgroundImgID, "fTexture", GL_TEXTURE0);
			shader->setFloat("progress", progress);
			wrapperGL::GLWrapper::draw(backgroundVID);

			//check if all tasks are loaded, if yes then switch to game controller
			if (progress >= 1.0) 
			{
				renderer::Easy3D::setContorller(global::Controllers::World3D);
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