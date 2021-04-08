#include "GLB_BLock.hpp"
#include "GLW_GLWrapper.hpp"
#include "GLB_Texture.hpp"


using namespace global::resource::texture;
#define LINK_INFO1(blockType, texture, textureN, textureOS, mid, attachment) list[static_cast<unsigned int>(blockType)] = new BlockRenderInfo(static_cast<unsigned int>(blockType) ,TextureMaker::getTexture(texture).id, TextureMaker::getTexture(textureN).id, TextureMaker::getTexture(textureOS).id, mesh::MeshMaker::getMesh(mid), attachment);
#define LINK_INFO(blockType, texture, textureN, textureOS) list[static_cast<unsigned int>(blockType)] = new BlockRenderInfo(static_cast<unsigned int>(blockType) ,TextureMaker::getTexture(texture).id, TextureMaker::getTexture(textureN).id, TextureMaker::getTexture(textureOS).id);
namespace global
{
	namespace resource
	{
		namespace block
		{
			const VAOID* BlockRenderInfo::getMeshID() 
			{
				return meshID;
			}

			const unsigned int& BlockRenderInfo::getTextureID()
			{
				return textureID;
			}

			const unsigned int& BlockRenderInfo::getNormalID()
			{
				return normalID;
			}

			const unsigned int& BlockRenderInfo::getOSID()
			{
				return OSID;
			}

			const unsigned short int& BlockRenderInfo::getProperties() 
			{
				return properties;
			}

			const unsigned int& BlockRenderInfo::getTypeID() 
			{
				return typeID;
			}

			BlockRenderInfo* BlockRenderInfoMaker::list[static_cast<unsigned int>(BlockType::LAST)];

			std::atomic<unsigned int> BlockRenderInfoMaker::currentProgress;

			void BlockRenderInfoMaker::init() 
			{
				currentProgress = 0;
			}

			float BlockRenderInfoMaker::getLoadingProgress() 
			{
				unsigned int temp = currentProgress.load();
				return (float)temp / static_cast<unsigned int>(BlockType::LAST);
			}

			void BlockRenderInfoMaker::load() 
			{
				using tx = TextureMaker::TextureName;
				using blk = BlockType;
				using info = BlockRenderInfo;
				using midInfo = mesh::MeshMaker::MeshType;

				//air renderable info
				LINK_INFO1(blk::AIR, tx::STONE, tx::STONE_N, tx::STONE_OS, midInfo::CUBES, info::TYPE_BLOCK | info::ATTACHMENT_INVISIBLE);
				currentProgress++;

				//stone 
				LINK_INFO(blk::STONE, tx::STONE, tx::STONE_N, tx::STONE_OS);
				currentProgress++;

				//dirt 
				LINK_INFO(blk::DIRT, tx::DIRT, tx::DIRT_N, tx::DIRT_OS);
				currentProgress++;

				//cobble stone
				LINK_INFO(blk::COBBLESTONE, tx::COBBLESTONE, tx::COBBLESTONE_N, tx::COBBLESTONE_OS);
				currentProgress++;

				//oak plank
				LINK_INFO(blk::OAK_PLANKS, tx::OAK_PLANKS, tx::OAK_PLANKS_N, tx::OAK_PLANKS_OS);
				currentProgress++;

				//spruce plank
				LINK_INFO(blk::SPRUCE_PLANKS, tx::SPRUCE_PLANKS, tx::SPRUCE_PLANKS_N, tx::SPRUCE_PLANKS_OS);
				currentProgress++;

				//birch plank
				LINK_INFO(blk::BIRCH_PLANKS, tx::BIRCH_PLANKS, tx::BIRCH_PLANKS_N, tx::BIRCH_PLANKS_OS);
				currentProgress++;

				//jungle plank
				LINK_INFO(blk::JUNGLE_PLANKS, tx::JUNGLE_PLANKS, tx::JUNGLE_PLANKS_N, tx::JUNGLE_PLANKS_OS);
				currentProgress++;

				//acacia plank
				LINK_INFO(blk::ACACIA_PLANKS, tx::ACACIA_PLANKS, tx::ACACIA_PLANKS_N, tx::ACACIA_PLANKS_OS);
				currentProgress++;

				//dark oak plank
				LINK_INFO(blk::DARK_OAK_PLANKS, tx::DARK_OAK_PLANKS, tx::DARK_OAK_PLANKS_N, tx::DARK_OAK_PLANKS_OS);
				currentProgress++;

				//bedrock
				LINK_INFO(blk::BEDROCK, tx::BEDROCK, tx::BEDROCK_N, tx::BEDROCK_OS);
				currentProgress++;

				//sand
				LINK_INFO(blk::SAND, tx::SAND, tx::SAND_N, tx::SAND_OS);
				currentProgress++;

				//grass block
				LINK_INFO(blk::GRASS, tx::GRASS, tx::GRASS_N, tx::GRASS_OS);
				currentProgress++;

				//mossy cobble stone
				LINK_INFO(blk::COBBLESTONE_MOSSY, tx::COBBLESTONE_MOSSY, tx::COBBLESTONE_MOSSY_N, tx::COBBLESTONE_MOSSY_OS);
				currentProgress++;

				//still water
				LINK_INFO1(blk::WATER, tx::WATER, tx::WATER_N, tx::WATER_OS, midInfo::CUBES, info::TYPE_LIQUID | info::ATTACHMENT_VISIBLE);
				currentProgress++;

				//still water top
				LINK_INFO1(blk::WATER_TOP, tx::WATER, tx::WATER_N, tx::WATER_OS, midInfo::WATER_TOP_CUBES, info::TYPE_LIQUID | info::ATTACHMENT_VISIBLE);
				currentProgress++;
				
			}

			BlockRenderInfo* BlockRenderInfoMaker::getBlockRenderInfo(BlockType which) 
			{
				return list[static_cast<unsigned int>(which)];
			}

		}
		
	}
}