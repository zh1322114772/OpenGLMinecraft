#pragma once
#include <string>
#include "GLW_Types.hpp"

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


namespace game
{
	namespace config 
	{
		namespace resource 
		{
			/// <summary>
			/// loaded texture ids
			/// </summary>

			class TextureIDs 
			{
			public:
				static wrapperGL::TextureID IDList[CFG_TEXTURE_ID_LAST];
			};

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