#include "GLB_Resources.hpp"
#include "GLW_GLWrapper.hpp"
#include "Render_Vertices.hpp"

#define TEX_PARA(arg) TextureIDs::blockTextureIDList[arg].id, TextureIDs::blockNormalIDList[arg].id, TextureIDs::blockOSIDList[arg].id
namespace global
{
	namespace resource
	{
		wrapperGL::TextureID TextureIDs::blockTextureIDList[CFG_TEXTURE_ID_LAST];
		wrapperGL::TextureID TextureIDs::blockNormalIDList[CFG_TEXTURE_ID_LAST];
		wrapperGL::TextureID TextureIDs::blockOSIDList[CFG_TEXTURE_ID_LAST];

		wrapperGL::VAOID VAOObjectList::cube;
		wrapperGL::VAOID VAOObjectList::cubes;

		blocks::BlockRenderableProperties* BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_LAST];
			
		/// <summary>
		/// list of all texture file names
		/// </summary>
		char TextureFileNameList::idList[CFG_TEXTURE_ID_LAST][48] = {"stone", 
																	"dirt",
																	"cobblestone",
																	"planks_oak",
																	"planks_spruce",
																	"planks_birch",
																	"planks_jungle",
																	"planks_acacia",
																	"planks_big_oak",
																	"bedrock",
																	"sand",
																	"grass",
																	"cobblestone_mossy",
																	"water_still"};

		std::string TextureFileNameList::getName(CFG_TEXTURE_ID id) 
		{
			return std::string(CFG_TEXTURE_DIRECTORY) + std::string(idList[id]);
		}

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
			
		/// <summary>
		/// load all block render infos
		/// </summary>
		void BlockRenderableInfoIDs::load() 
		{
			using namespace blocks;
			using namespace global::resource;

			//air
			// set air block to invisible
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_AIR] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_STONE), BlockRenderableProperties::TYPE_BLOCK | BlockRenderableProperties::ATTACHMENT_INVISIBLE);

			//stone
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_STONE] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_STONE));

			//dirt
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_DIRT] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_DIRT));

			//cobble stone
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_COBBLESTONE] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_COBBLESTONE));

			//oak planks
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_OAK_PLANKS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_OAK_PLANKS));

			//SPRUCE_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_SPRUCE_PLANKS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_SPRUCE_PLANKS));

			//BRICH_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_BRICH_PLANKS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_BRICH_PLANKS));

			//JUNGLE_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_JUNGLE_PLANKS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_JUNGLE_PLANKS));

			//ACACIA_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_ACACIA_PLANKS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_ACACIA_PLANKS));

			//DARK_OAK_PLANK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_DARK_OAK_PLANKS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_DARK_OAK_PLANKS));

			//BEDROCK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_BEDROCK));

			//BEDROCK
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_BEDROCK));

			//SAND
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_SAND] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_SAND));

			//GRASS
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_GRASS] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_GRASS));

			//COBBLE STONE MOSSY
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_COBBLESTONE_MOSSY] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_COBBLESTONE_MOSSY));

			//WATER
			BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_WATER] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_WATER), BlockRenderableProperties::ATTACHMENT_VISIBLE | BlockRenderableProperties::TYPE_LIQUID);
		}
		
	}
}