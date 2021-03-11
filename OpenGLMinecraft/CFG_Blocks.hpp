#pragma once
#include "CFG_Resources.hpp"
namespace game
{
	namespace config
	{
		namespace blocks
		{
			//define all blocks in game
			struct Block
			{
				CFG_BLCOKMESH_ID blockID;

				bool hide = false;

				Block(CFG_BLCOKMESH_ID id) : blockID(id)
				{

				}

				Block() 
				{
					blockID = CFG_BLOCKMESH_ID_STONE;
				}
			};

			//define some blocks
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

			struct CobbleStone : public Block
			{
				CobbleStone() :Block(CFG_BLOCKMESH_ID_COBBLESTONE)
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

		}
	}
}