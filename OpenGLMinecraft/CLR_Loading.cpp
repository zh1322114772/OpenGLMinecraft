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

			//load vertices
			using namespace game::config::resource;

			//cube
			auto vaoList = renderer::Vertices::cubeGenerator(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0));
			VAOObjectList::cube = wrapperGL::GLWrapper::loadVAOS(vaoList);
			delete vaoList;

			verticesLoaderProgress = 1.0;
		}

		void Loading::meshBlockLoader() 
		{
			//check if textureloader is completed
			if (verticesLoaderProgress < 1.0) return;
			
			using namespace renderer::controllers::world3D;
			using namespace game::config::resource;

			//stone
			TextureBundle face_a(TextureIDs::IDList[CFG_TEXTURE_ID_STONE]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_STONE] = new BlockMesh(face_a, VAOObjectList::cube);

			//dirt
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_DIRT]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_DIRT] = new BlockMesh(face_a, VAOObjectList::cube);

			//cobble stone
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_COBBLESTONE]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_COBBLESTONE] = new BlockMesh(face_a, VAOObjectList::cube);

			//oak planks
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_OAK_PLANKS]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_OAK_PLANKS] = new BlockMesh(face_a, VAOObjectList::cube);

			//SPRUCE_PLANK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_SPRUCE_PLANKS]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_SPRUCE_PLANKS] = new BlockMesh(face_a, VAOObjectList::cube);

			//BRICH_PLANK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_BRICH_PLANKS]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_BRICH_PLANKS] = new BlockMesh(face_a, VAOObjectList::cube);

			//JUNGLE_PLANK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_JUNGLE_PLANKS]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_JUNGLE_PLANKS] = new BlockMesh(face_a, VAOObjectList::cube);

			//ACACIA_PLANK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_ACACIA_PLANKS]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_ACACIA_PLANKS] = new BlockMesh(face_a, VAOObjectList::cube);

			//DARK_OAK_PLANK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_DARK_OAK_PLANKS]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_DARK_OAK_PLANKS] = new BlockMesh(face_a, VAOObjectList::cube);

			//BEDROCK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_BEDROCK]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockMesh(face_a, VAOObjectList::cube);

			//BEDROCK
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_BEDROCK]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockMesh(face_a, VAOObjectList::cube);

			//SAND
			face_a = TextureBundle(TextureIDs::IDList[CFG_TEXTURE_ID_SAND]);
			BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_SAND] = new BlockMesh(face_a, VAOObjectList::cube);

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