#pragma once
#include <atomic>
#include <iostream>
#include "GLB_Mesh.hpp"

#define BLOCK_TYPE(type) BlockRenderInfoMaker::getBlockRenderInfo(type)
namespace global
{
	namespace resource
	{
		namespace block 
		{

			class BlockRenderInfo final
			{
			public:
				/// <summary>
				/// block type
				/// </summary>
				static const unsigned short int TYPE_BLOCK = 0b0;
				static const unsigned short int TYPE_LIQUID = 0b1;

				/// <summary>
				/// additional block attachment
				/// </summary>
				static const unsigned short int ATTACHMENT_INVISIBLE = 0b00;
				static const unsigned short int ATTACHMENT_VISIBLE = 0b10;
				static const unsigned short int ATTACHMENT_TRANSPARENT = 0b100;
				static const unsigned short int ATTACHMENT_RELFECT = 0b1000;

			private:
				/// <summary>
				/// mesh id
				/// </summary>
				const VAOID* meshID;

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
				unsigned short int properties;

				/// <summary>
				/// blocktype id
				/// </summary>
				unsigned int typeID;



			public:

				/// <summary>
				/// get texture id
				/// </summary>
				/// <returns></returns>
				const unsigned int& getTextureID();

				/// <summary>
				/// get normal map id
				/// </summary>
				/// <returns></returns>
				const unsigned int& getNormalID();

				/// <summary>
				/// get occlusion & specular map
				/// </summary>
				/// <returns></returns>
				const unsigned int& getOSID();

				/// <summary>
				/// get render info properties
				/// </summary>
				/// <returns></returns>
				const unsigned short int& getProperties();

				/// <summary>
				/// return block render info type id
				/// </summary>
				/// <returns></returns>
				const unsigned int& getTypeID();

				/// <summary>
				/// return render mesh id
				/// </summary>
				/// <returns></returns>
				const VAOID* getMeshID();

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="id">block render info type id</param>
				///
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <param name="t">additional info</param>
				/// <returns></returns>
				BlockRenderInfo(unsigned int id ,unsigned int tid, unsigned int nid, unsigned short int osid, const VAOID* mid = mesh::MeshMaker::getMesh(mesh::MeshMaker::MeshType::CUBES), unsigned short int t = TYPE_BLOCK | ATTACHMENT_VISIBLE) :typeID(id), textureID(tid), normalID(nid), OSID(osid), properties(t), meshID(mid)
				{

				}

			};
		
			/// <summary>
			/// this class make block render info
			/// </summary>
			class BlockRenderInfoMaker final
			{
			public:
				enum class BlockType
				{
					AIR,
					STONE,
					DIRT,
					COBBLESTONE,
					OAK_PLANKS,
					SPRUCE_PLANKS,
					BIRCH_PLANKS,
					JUNGLE_PLANKS,
					ACACIA_PLANKS,
					DARK_OAK_PLANKS,
					BEDROCK,
					SAND,
					GRASS,
					COBBLESTONE_MOSSY,

					WATER_TOP,
					WATER,

					LAST
				};

				/// <summary>
				/// load all block render info prototypes
				/// </summary>
				static void load();

				/// <summary>
				/// return block render info
				/// </summary>
				/// <param name="which">which block</param>
				/// <returns></returns>
				static BlockRenderInfo* getBlockRenderInfo(BlockType which);

				/// <summary>
				/// get current loading progress
				/// </summary>
				/// <returns></returns>
				static float getLoadingProgress();

				/// <summary>
				/// init
				/// </summary>
				static void init();

			private:
				static BlockRenderInfo* list[static_cast<unsigned int>(BlockType::LAST)];

				/// <summary>
				/// current loading progress
				/// </summary>
				static std::atomic<unsigned int> currentProgress;

			
			};





			using bid = BlockRenderInfoMaker::BlockType;


			//block base struct
			struct Block
			{
				BlockRenderInfo* renderInfo;

				//if block is able to pass through
				bool passThrough;

				Block(BlockRenderInfo* info, bool pt) : renderInfo(info), passThrough(pt)
				{

				}

				Block() : renderInfo(BLOCK_TYPE(bid::AIR)), passThrough(true)
				{

				}
			};


			//other blocks
			struct AirBlock : public Block
			{
				AirBlock() :Block(BLOCK_TYPE(bid::AIR), true)
				{

				}
			};


			struct DirtBlock : public Block
			{
				DirtBlock() :Block(BLOCK_TYPE(bid::DIRT), false)
				{

				}
			};

			struct StoneBlock : public Block
			{
				StoneBlock() :Block(BLOCK_TYPE(bid::STONE), false)
				{

				}
			};

			struct CobbleStoneBlock : public Block
			{
				CobbleStoneBlock() :Block(BLOCK_TYPE(bid::COBBLESTONE), false)
				{

				}
			};

			struct OakPlankBlock : public Block
			{
				OakPlankBlock() :Block(BLOCK_TYPE(bid::OAK_PLANKS), false)
				{

				}
			};

			struct SprucePlankBlock : public Block
			{
				SprucePlankBlock() :Block(BLOCK_TYPE(bid::SPRUCE_PLANKS), false)
				{

				}
			};

			struct BirchPlankBlock : public Block
			{
				BirchPlankBlock() :Block(BLOCK_TYPE(bid::BIRCH_PLANKS), false)
				{

				}
			};

			struct JunglePlankBlock : public Block
			{
				JunglePlankBlock() :Block(BLOCK_TYPE(bid::JUNGLE_PLANKS), false)
				{

				}
			};

			struct AcaciaPlankBlock : public Block
			{
				AcaciaPlankBlock() :Block(BLOCK_TYPE(bid::ACACIA_PLANKS), false)
				{

				}
			};

			struct DarkOakPlankBlock : public Block
			{
				DarkOakPlankBlock() :Block(BLOCK_TYPE(bid::DARK_OAK_PLANKS), false)
				{

				}
			};

			struct BedrockBlock : public Block
			{
				BedrockBlock() :Block(BLOCK_TYPE(bid::BEDROCK), false)
				{

				}
			};

			struct SandBlock : public Block
			{
				SandBlock() :Block(BLOCK_TYPE(bid::SAND), false)
				{

				}
			};

			struct GrassBlock : public Block
			{
				GrassBlock() :Block(BLOCK_TYPE(bid::GRASS), false)
				{

				}
			};

			struct CobbleStoneMossyBlock : public Block
			{
				CobbleStoneMossyBlock() : Block(BLOCK_TYPE(bid::COBBLESTONE_MOSSY), false)
				{

				}
			};

			struct WaterBlock : public Block
			{
				WaterBlock() : Block(BLOCK_TYPE(bid::WATER), true)
				{

				}
			};
			
			struct WaterTopBlock : public Block
			{
				WaterTopBlock() : Block(BLOCK_TYPE(bid::WATER_TOP), true)
				{

				}
			};
			

		
		}
	}

}