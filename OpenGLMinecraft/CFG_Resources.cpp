#include "CFG_Resources.hpp"
#include "GLW_GLWrapper.hpp"
#include "Render_Vertices.hpp"

namespace game
{
	namespace config
	{
		namespace resource
		{
			wrapperGL::TextureID TextureIDs::IDList[CFG_TEXTURE_ID_LAST];

			wrapperGL::VAOID VAOObjectList::cube;
			wrapperGL::VAOID VAOObjectList::cubes;

			renderer::controllers::world3D::BlockMesh* BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_LAST];
			
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
																		"sand"};

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
				vaoList = renderer::Vertices::cubesGenerator(24, glm::vec3(0.0));
				VAOObjectList::cubes = wrapperGL::GLWrapper::loadVAOS(vaoList);
				delete vaoList;
			}
			
			/// <summary>
			/// load all block meshes
			/// </summary>
			void BlockMeshIDs::load() 
			{
				using namespace renderer::controllers::world3D;
				using namespace game::config::resource;

				//air
				// set air block to invisible
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_AIR] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_STONE], BlockMesh::INVISIBLE);

				//stone
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_STONE] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_STONE]);

				//dirt
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_DIRT] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_DIRT]);

				//cobble stone
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_COBBLESTONE] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_COBBLESTONE]);

				//oak planks
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_OAK_PLANKS] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_OAK_PLANKS]);

				//SPRUCE_PLANK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_SPRUCE_PLANKS] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_SPRUCE_PLANKS]);

				//BRICH_PLANK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_BRICH_PLANKS] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_BRICH_PLANKS]);

				//JUNGLE_PLANK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_JUNGLE_PLANKS] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_JUNGLE_PLANKS]);

				//ACACIA_PLANK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_ACACIA_PLANKS] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_ACACIA_PLANKS]);

				//DARK_OAK_PLANK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_DARK_OAK_PLANKS] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_DARK_OAK_PLANKS]);

				//BEDROCK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_BEDROCK]);

				//BEDROCK
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_BEDROCK] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_BEDROCK]);

				//SAND
				BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_SAND] = new BlockMesh(TextureIDs::IDList[CFG_TEXTURE_ID_SAND]);
			}
		
		}

	}
}