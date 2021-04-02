#pragma once
#include <string>
#include "GLW_Types.hpp"

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
		//define all blocks in the game
		namespace blocks
		{
			/// <summary>
			/// block render infos
			/// </summary>
			struct BlockRenderableProperties
			{
				static const unsigned short int TYPE_BLOCK = 0b0;
				static const unsigned short int TYPE_LIQUID = 0b1;

				static const unsigned short int ATTACHMENT_INVISIBLE = 0b00;
				static const unsigned short int ATTACHMENT_VISIBLE = 0b10;
				static const unsigned short int ATTACHMENT_TRANSPARENT = 0b100;
				static const unsigned short int ATTACHMENT_RELFECT = 0b1000;

				/// <summary>
				/// texture id
				/// </summary>
				unsigned int textureID;

				/// <summary>
				/// normal map id
				/// </summary>
				unsigned int normalID;

				/// <summary>
				/// specular and occlusion map id
				/// </summary>
				unsigned int OSID;

				/// <summary>
				/// additional properties to the block
				/// </summary>
				unsigned short int properties = TYPE_BLOCK | ATTACHMENT_VISIBLE;

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <returns></returns>
				BlockRenderableProperties(unsigned int tid, unsigned int nid, unsigned short int osid) :textureID(tid), normalID(nid), OSID(osid)
				{

				}

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <param name="t">if texture is transparent</param>
				/// <returns></returns>
				BlockRenderableProperties(unsigned int tid, unsigned int nid, unsigned int osid, unsigned short int t) : properties(t), textureID(tid), normalID(nid), OSID(osid)
				{

				}
			};



			//block base struct
			struct Block
			{
				CFG_BLCOKMESH_ID blockID;

				//if block is able to pass through
				bool passThrough;

				Block(CFG_BLCOKMESH_ID id, bool pt) : blockID(id), passThrough(pt)
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
				AirBlock() :Block(CFG_BLOCKMESH_ID_AIR, true)
				{

				}
			};


			struct DirtBlock : public Block
			{
				DirtBlock() :Block(CFG_BLOCKMESH_ID_DIRT, false)
				{

				}
			};

			struct StoneBlock : public Block
			{
				StoneBlock() :Block(CFG_BLOCKMESH_ID_STONE, false)
				{

				}
			};

			struct CobbleStoneBlock : public Block
			{
				CobbleStoneBlock() :Block(CFG_BLOCKMESH_ID_COBBLESTONE, false)
				{

				}
			};

			struct OakPlankBlock : public Block
			{
				OakPlankBlock() :Block(CFG_BLOCKMESH_ID_OAK_PLANKS, false)
				{

				}
			};

			struct SprucePlankBlock : public Block
			{
				SprucePlankBlock() :Block(CFG_BLOCKMESH_ID_SPRUCE_PLANKS, false)
				{

				}
			};

			struct BrichPlankBlock : public Block
			{
				BrichPlankBlock() :Block(CFG_BLOCKMESH_ID_BRICH_PLANKS, false)
				{

				}
			};

			struct JunglePlankBlock : public Block
			{
				JunglePlankBlock() :Block(CFG_BLOCKMESH_ID_JUNGLE_PLANKS, false)
				{

				}
			};

			struct AcaciaPlankBlock : public Block
			{
				AcaciaPlankBlock() :Block(CFG_BLOCKMESH_ID_ACACIA_PLANKS, false)
				{

				}
			};

			struct DarkOakPlankBlock : public Block
			{
				DarkOakPlankBlock() :Block(CFG_BLOCKMESH_ID_DARK_OAK_PLANKS, false)
				{

				}
			};

			struct BedrockBlock : public Block
			{
				BedrockBlock() :Block(CFG_BLOCKMESH_ID_BEDROCK, false)
				{

				}
			};

			struct SandBlock : public Block
			{
				SandBlock() :Block(CFG_BLOCKMESH_ID_SAND, false)
				{

				}
			};

			struct GrassBlock : public Block
			{
				GrassBlock() :Block(CFG_BLOCKMESH_ID_GRASS, false)
				{

				}
			};

			struct CobbleStoneMossyBlock : public Block
			{
				CobbleStoneMossyBlock() : Block(CFG_BLOCKMESH_ID_COBBLESTONE_MOSSY, false)
				{

				}
			};

			struct WaterBlock : public Block
			{
				WaterBlock() : Block(CFG_BLOCKMESH_ID_WATER, true)
				{

				}
			};
		}

		//define all entites in the game
		namespace entities
		{
			class Entity
			{


			};

		}


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
		struct BlockRenderableInfoIDs 
		{
			static blocks::BlockRenderableProperties* IDList[CFG_BLOCKMESH_ID_LAST];

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
	}
	
}