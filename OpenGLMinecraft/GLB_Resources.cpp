#include "GLB_Resources.hpp"
#include "GLW_GLWrapper.hpp"
#include "Render_Vertices.hpp"
#include "GLB_Texture.hpp"

#define TEX_PARA(arg) TextureIDs::blockTextureIDList[arg].id, TextureIDs::blockNormalIDList[arg].id, TextureIDs::blockOSIDList[arg].id
namespace global
{
	namespace resource
	{

		wrapperGL::VAOID VAOObjectList::cube;
		wrapperGL::VAOID VAOObjectList::cubes;

		blocks::BlockRenderableProperties* BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_LAST];
			

		/// <summary>
		/// load all vertices
		/// </summary>
		void VAOObjectList::load() 
		{

			//cube
			auto vaoList = renderer::Vertices::cubeGenerator(glm::vec3(0.0), glm::vec3(1.0), glm::vec3(0.0));
			VAOObjectList::cube = wrapperGL::GLWrapper::loadVAOS(vaoList);
			delete vaoList;

			//cubes
			vaoList = renderer::Vertices::cubesGenerator(256, glm::vec3(0.0, 0.0, 1.0));
			VAOObjectList::cubes = wrapperGL::GLWrapper::loadVAOS(vaoList);
			delete vaoList;
		}
		
		/**
		/// <summary>
		/// load all block render infos
		/// </summary>
		void BlockRenderableInfoIDs::load() 
		{
			using namespace blocks;
			using namespace global::resource::texture;

			//air
			// set air block to invisible
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_AIR] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::STONE).id, TextureMaker::getTexture(TextureMaker::TextureName::STONE_N).id, TextureMaker::getTexture(TextureMaker::TextureName::STONE_OS).id, BlockRenderableProperties::TYPE_BLOCK | BlockRenderableProperties::ATTACHMENT_INVISIBLE);

			//stone
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_STONE] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::STONE).id, TextureMaker::getTexture(TextureMaker::TextureName::STONE_N).id, TextureMaker::getTexture(TextureMaker::TextureName::STONE_OS).id);

			//dirt
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_DIRT] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::DIRT).id, TextureMaker::getTexture(TextureMaker::TextureName::DIRT_N).id, TextureMaker::getTexture(TextureMaker::TextureName::DIRT_OS).id);

			//cobble stone
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_COBBLESTONE] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::COBBLESTONE).id, TextureMaker::getTexture(TextureMaker::TextureName::COBBLESTONE_N).id, TextureMaker::getTexture(TextureMaker::TextureName::COBBLESTONE_OS).id);

			//oak planks
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_OAK_PLANKS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::OAK_PLANKS).id, TextureMaker::getTexture(TextureMaker::TextureName::OAK_PLANKS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::OAK_PLANKS_OS).id);

			//SPRUCE_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_SPRUCE_PLANKS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::SPRUCE_PLANKS).id, TextureMaker::getTexture(TextureMaker::TextureName::SPRUCE_PLANKS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::SPRUCE_PLANKS_OS).id);

			//BRICH_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_BRICH_PLANKS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::BIRCH_PLANKS).id, TextureMaker::getTexture(TextureMaker::TextureName::BIRCH_PLANKS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::BIRCH_PLANKS_OS).id);

			//JUNGLE_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_JUNGLE_PLANKS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::JUNGLE_PLANKS).id, TextureMaker::getTexture(TextureMaker::TextureName::JUNGLE_PLANKS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::JUNGLE_PLANKS_OS).id);

			//ACACIA_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_ACACIA_PLANKS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::ACACIA_PLANKS).id, TextureMaker::getTexture(TextureMaker::TextureName::ACACIA_PLANKS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::ACACIA_PLANKS_OS).id);

			//DARK_OAK_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_DARK_OAK_PLANKS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::DARK_OAK_PLANKS).id, TextureMaker::getTexture(TextureMaker::TextureName::DARK_OAK_PLANKS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::DARK_OAK_PLANKS_OS).id);

			//BEDROCK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::BEDROCK).id, TextureMaker::getTexture(TextureMaker::TextureName::BEDROCK_N).id, TextureMaker::getTexture(TextureMaker::TextureName::BEDROCK_OS).id);

			//SAND
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_SAND] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::SAND).id, TextureMaker::getTexture(TextureMaker::TextureName::SAND_N).id, TextureMaker::getTexture(TextureMaker::TextureName::SAND_OS).id);

			//GRASS
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_GRASS] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::GRASS).id, TextureMaker::getTexture(TextureMaker::TextureName::GRASS_N).id, TextureMaker::getTexture(TextureMaker::TextureName::GRASS_OS).id);

			//COBBLE STONE MOSSY
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_COBBLESTONE_MOSSY] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::COBBLESTONE_MOSSY).id, TextureMaker::getTexture(TextureMaker::TextureName::COBBLESTONE_MOSSY_N).id, TextureMaker::getTexture(TextureMaker::TextureName::COBBLESTONE_MOSSY_OS).id);

			//WATER
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_WATER] = new BlockRenderableProperties(TextureMaker::getTexture(TextureMaker::TextureName::WATER).id, TextureMaker::getTexture(TextureMaker::TextureName::WATER_N).id, TextureMaker::getTexture(TextureMaker::TextureName::WATER_OS).id, BlockRenderableProperties::ATTACHMENT_VISIBLE | BlockRenderableProperties::TYPE_LIQUID);
		}
		*/

	}
}