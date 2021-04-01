#pragma once
#include <string>
#include "GLW_Types.hpp"
#include "CLR_World3DTypes.hpp"

//texture ids
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
	CFG_TEXTURE_ID_GRASS,
	CFG_TEXTURE_ID_COBBLESTONE_MOSSY,
	CFG_TEXTURE_ID_WATER,

	CFG_TEXTURE_ID_LAST
};

#define CFG_TEXTURE_DIRECTORY "data\\textures\\blocks\\"

//block mesh ids
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
	CFG_BLOCKMESH_ID_GRASS,
	CFG_BLOCKMESH_ID_COBBLESTONE_MOSSY,
	CFG_BLOCKMESH_ID_WATER,

	CFG_BLOCKMESH_ID_LAST
};


namespace global
{

	namespace resource 
	{
		struct VAOObjectList 
		{
			static wrapperGL::VAOID cube;
			static wrapperGL::VAOID cubes;

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
			static renderer::controllers::world3DTypes::BlockMesh* IDList[CFG_BLOCKMESH_ID_LAST];

			/// <summary>
			/// load all block meshes
			/// </summary>
			static void load();
		};

		/// <summary>
		/// loaded texture id list
		/// </summary>
		struct TextureIDs 
		{
			static wrapperGL::TextureID blockTextureIDList[CFG_TEXTURE_ID_LAST];
			static wrapperGL::TextureID blockNormalIDList[CFG_TEXTURE_ID_LAST];
			static wrapperGL::TextureID blockOSIDList[CFG_TEXTURE_ID_LAST];
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

		//define all blocks in the game
		namespace blocks 
		{
			//block base struct
			struct Block
			{
				CFG_BLCOKMESH_ID blockID;

				Block(CFG_BLCOKMESH_ID id) : blockID(id)
				{

				}

				Block()
				{
					blockID = CFG_BLOCKMESH_ID_STONE;
				}
			};




			//other blocks
			struct AirBlock : public Block
			{
				AirBlock() :Block(CFG_BLOCKMESH_ID_AIR)
				{

				}
			};


			struct DirtBlock : public Block
			{
				DirtBlock() :Block(CFG_BLOCKMESH_ID_DIRT)
				{

				}
			};

			struct StoneBlock : public Block
			{
				StoneBlock() :Block(CFG_BLOCKMESH_ID_STONE)
				{

				}
			};

			struct CobbleStoneBlock : public Block
			{
				CobbleStoneBlock() :Block(CFG_BLOCKMESH_ID_COBBLESTONE)
				{

				}
			};

			struct OakPlankBlock : public Block
			{
				OakPlankBlock() :Block(CFG_BLOCKMESH_ID_OAK_PLANKS)
				{

				}
			};

			struct SprucePlankBlock : public Block
			{
				SprucePlankBlock() :Block(CFG_BLOCKMESH_ID_SPRUCE_PLANKS)
				{

				}
			};

			struct BrichPlankBlock : public Block
			{
				BrichPlankBlock() :Block(CFG_BLOCKMESH_ID_BRICH_PLANKS)
				{

				}
			};

			struct JunglePlankBlock : public Block
			{
				JunglePlankBlock() :Block(CFG_BLOCKMESH_ID_JUNGLE_PLANKS)
				{

				}
			};

			struct AcaciaPlankBlock : public Block
			{
				AcaciaPlankBlock() :Block(CFG_BLOCKMESH_ID_ACACIA_PLANKS)
				{

				}
			};

			struct DarkOakPlankBlock : public Block
			{
				DarkOakPlankBlock() :Block(CFG_BLOCKMESH_ID_DARK_OAK_PLANKS)
				{

				}
			};

			struct BedrockBlock : public Block
			{
				BedrockBlock() :Block(CFG_BLOCKMESH_ID_BEDROCK)
				{

				}
			};

			struct SandBlock : public Block
			{
				SandBlock() :Block(CFG_BLOCKMESH_ID_SAND)
				{

				}
			};

			struct GrassBlock : public Block
			{
				GrassBlock() :Block(CFG_BLOCKMESH_ID_GRASS)
				{

				}
			};

			struct CobbleStoneMossyBlock : public Block
			{
				CobbleStoneMossyBlock() : Block(CFG_BLOCKMESH_ID_COBBLESTONE_MOSSY)
				{

				}
			};

			struct WaterBlock : public Block
			{
				WaterBlock() : Block(CFG_BLOCKMESH_ID_WATER)
				{

				}
			};
		}


	}
	
}