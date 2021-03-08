#include "CFG_Resources.hpp"

namespace game
{
	namespace config
	{
		namespace resource
		{
			wrapperGL::TextureID TextureIDs::IDList[CFG_TEXTURE_ID_LAST];

			wrapperGL::VAOID VAOObjectList::cube;

			renderer::controllers::world3D::BlockMesh* BlockMeshIDs::IDList[CFG_BLOCKMESH_ID_LAST];
			
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


		
		
		
		}

	}
}