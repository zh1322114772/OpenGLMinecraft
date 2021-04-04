#include "GLB_BLock.hpp"
#include "GLW_GLWrapper.hpp"
//#define TEX_PARA(arg) TextureIDs::blockTextureIDList[arg].id, TextureIDs::blockNormalIDList[arg].id, TextureIDs::blockOSIDList[arg].id

#define LINK_INFO(blockType, textureType, attachment) list[static_cast<unsigned int>(blockType)] = new BlockRenderInfo()
namespace global
{
	namespace resource
	{
		namespace block
		{
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

			void BlockRenderInfoMaker::load() 
			{
				//list[static_cast<unsigned int>(BlockType::AIR)] = new BlockRenderInfo(,,,)

				//BlockRenderableInfoIDs::IDList[CFG_BLOCKMESH_ID_AIR] = new BlockRenderableProperties(TEX_PARA(CFG_TEXTURE_ID_STONE), BlockRenderableProperties::TYPE_BLOCK | BlockRenderableProperties::ATTACHMENT_INVISIBLE);
			}

			BlockRenderInfo* BlockRenderInfoMaker::getBlockRenderInfo(BlockType which) 
			{
				
			}

		}
		
		


	}
}