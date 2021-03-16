#pragma once
#include "CLR_Loading.hpp"
#include "GLW_GLWrapper.hpp"
#include "GLSL_Code.hpp"
#include "Render_Vertices.hpp"
#include <iostream>
#include "CFG_Resources.hpp"
#include "Renderer.hpp"
#include "CFG_ControllerIDs.hpp"
#include "BitMapProcess.hpp"
#include <string>

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
	
		std::tuple<wrapperGL::ImageObject*, wrapperGL::ImageObject*, wrapperGL::ImageObject*, wrapperGL::ImageObject*> Loading::loadBitMaps(const char* fileName) 
		{
			//construct file name
			std::string tName = fileName;
			std::string tPng = ".png";
			std::string tNormal = "_n";
			std::string tSpecular = "_s";
			std::string tOcclusion = "_o";

			using namespace wrapperGL;

			ImageObject* img;
			ImageObject* imgN;
			ImageObject* imgO;
			ImageObject* imgS;

			//load texture
			try 
			{
				img = GLWrapper::loadImage((tName + tPng).c_str());
			}
			catch (const std::exception& e) 
			{
				//if the texture is not exist, then it makes no sense to load other maps
				//so, just return 
				return std::make_tuple(nullptr, nullptr, nullptr, nullptr);
			}

			//load normal map
			try 
			{
				imgN = GLWrapper::loadImage((tName + tNormal + tPng).c_str());
			}
			catch (const std::exception& e) 
			{
				imgN = nullptr;
			}

			//load specular map
			try 
			{
				imgS = GLWrapper::loadImage((tName + tSpecular + tPng).c_str());
			}
			catch (const std::exception& e)
			{
				imgS = nullptr;
			}

			//load occlusion
			try 
			{
				imgO = GLWrapper::loadImage((tName + tOcclusion + tPng).c_str());
			}
			catch (const std::exception& e) 
			{
				imgO = nullptr;
			}

			return std::make_tuple(img, imgN, imgS, imgO);
		}

		wrapperGL::ImageObject* Loading::makeTexture(const char* fileName)
		{
			auto [img, imgN, imgS, imgO] = loadBitMaps(fileName);

			//if this block has a uniform texture
			if (img) 
			{
				//normal maps for different directions
				//nullptr for now, will be implemented later...
				wrapperGL::ImageObject* imgNRight = nullptr;
				wrapperGL::ImageObject* imgNBack = nullptr;
				wrapperGL::ImageObject* imgNLeft = nullptr;
				wrapperGL::ImageObject* imgNTop = nullptr;
				wrapperGL::ImageObject* imgNBottom = nullptr;

				//merge occlusion nad specular map together
				wrapperGL::ImageObject* mapOS = nullptr;
				if (imgS && imgO) 
				{
					//merge six 6 specular and 6 occlusion maps into 3 rgba maps
					mapOS = other::BitMapProcess::channelMerge(imgS, 0, imgO, 0, imgS, 0, imgO, 0);
				}

				//merge all bit maps into one
				auto ret = other::BitMapProcess::merge({ other::At(img, 0, 0),
													other::At(img, img->width, 0),
													other::At(img, img->width * 2, 0),
													other::At(img, img->width * 3, 0),
													other::At(img, img->width * 4, 0),
													other::At(img, img->width * 5, 0),
													other::At(imgN, img->width * 6, 0),
													other::At(imgNRight, img->width * 7, 0),
													other::At(imgNBack, img->width * 8, 0),
													other::At(imgNLeft, img->width * 9, 0),
													other::At(imgNTop, img->width * 10, 0),
													other::At(imgNBottom, img->width * 11, 0),
													other::At(mapOS, img->width * 12, 0),
													other::At(mapOS, img->width * 13, 0),
													other::At(mapOS, img->width * 14, 0) });

				//clean up
				delete img;
				delete imgN;
				delete imgO;
				delete imgS;
				delete imgNRight;
				delete imgNBack;
				delete imgNLeft;
				delete imgNTop;
				delete imgNBottom;
				delete mapOS;

				return ret;
			}
		
		}

		void Loading::textureLoader() 
		{
			if (textureLoaderProgressI < CFG_TEXTURE_ID_LAST) 
			{
				//more textures need to be loaded
				wrapperGL::ImageObject* imgObj = makeTexture(game::config::resource::TextureFileNameList::getName((CFG_TEXTURE_ID)textureLoaderProgressI).c_str());
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