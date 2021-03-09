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

			renderer::controllers::world3D::BlockMesh* BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_LAST];
			
			/// <summary>
			/// list of all texture file names
			/// </summary>
			char TextureFileNameList::idList[CFG_TEXTURE_ID_LAST][48] = {"stone.png", 
																		"dirt.png",
																		"cobblestone.png",
																		"planks_oak.png",
																		"planks_spruce.png",
																		"planks_birch.png",
																		"planks_jungle.png",
																		"planks_acacia.png",
																		"planks_big_oak.png",
																		"bedrock.png",
																		"sand.png"};

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
			}
			
			/// <summary>
			/// load all block meshes
			/// </summary>
			void BlockMeshIDs::load() 
			{
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
			}
		
		}

	}
}