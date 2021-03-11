#pragma once
#include <string>
#include "GLW_Types.hpp"
#include "CLR_World3D_Types.hpp"

//texture id
enum CFG_TEXTURE_ID
{
	CFG_TEXTURE_ID_STONE,
	CFG_TEXTURE_ID_DIRT,
	CFG_TEXTURE_ID_COBBLESTONE,
	CFG_TEXTURE_ID_OAK_PLANKS,
	CFG_TEXTURE_ID_SPRUCE_PLANKS,
	CFG_TEXTURE_ID_BRICH_PLANKS,
	CFG_TEXTURE_ID_JUNGLE_PLANKS,
	CFG_TEXTURE_ID_ACACIA_PLANKS,
	CFG_TEXTURE_ID_DARK_OAK_PLANKS,
	CFG_TEXTURE_ID_BEDROCK,
	CFG_TEXTURE_ID_SAND,

	CFG_TEXTURE_ID_LAST
};

#define CFG_TEXTURE_DIRECTORY "data\\textures\\blocks\\"

//block mesh id
enum CFG_BLCOKMESH_ID 
{
	CFG_BLOCKMESH_ID_AIR,
	CFG_BLOCKMESH_ID_STONE,
	CFG_BLOCKMESH_ID_DIRT,
	CFG_BLOCKMESH_ID_COBBLESTONE,
	CFG_BLOCKMESH_ID_OAK_PLANKS,
	CFG_BLOCKMESH_ID_SPRUCE_PLANKS,
	CFG_BLOCKMESH_ID_BRICH_PLANKS,
	CFG_BLOCKMESH_ID_JUNGLE_PLANKS,
	CFG_BLOCKMESH_ID_ACACIA_PLANKS,
	CFG_BLOCKMESH_ID_DARK_OAK_PLANKS,
	CFG_BLOCKMESH_ID_BEDROCK,
	CFG_BLOCKMESH_ID_SAND,

	CFG_BLOCKMESH_ID_LAST
};


namespace game
{
	namespace config 
	{
		namespace resource 
		{
			struct VAOObjectList 
			{
				static wrapperGL::VAOID cube;

				/// <summary>
				/// load all vertices
				/// </summary>
				static void load();
			};

			/// <summary>
			/// blockMsh id list
			/// </summary>
			struct BlockMeshIDs 
			{
				static renderer::controllers::world3D::BlockMesh* IDList[CFG_BLOCKMESH_ID_LAST];

				/// <summary>
				/// load all block meshes
				/// </summary>
				static void load();
			};

			/// <summary>
			/// texture id list
			/// </summary>
			struct TextureIDs 
			{
				static wrapperGL::TextureID IDList[CFG_TEXTURE_ID_LAST];
			};

			/// <summary>
			/// texture id file name list
			/// </summary>
			class TextureFileNameList 
			{
			private:
				/// <summary>
				/// array that contains file name for every texture id
				/// </summary>
				static char idList[CFG_TEXTURE_ID_LAST][48];

			public:

				/// <summary>
				/// get string file name from CFG_TEXTURE_ID
				/// </summary>
				/// <param name="id">texture id</param>
				/// <returns>string file name</returns>
				static std::string getName(CFG_TEXTURE_ID id);
			};

		}
	}
}