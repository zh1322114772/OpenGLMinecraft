#include "GLB_Texture.hpp"
#include "BitMapProcess.hpp"
#include "GLW_GLWrapper.hpp"
#include <string>
#include <stdexcept>
using namespace wrapperGL;

#define BLOCK_PATH "data\\textures\\blocks\\"

#define BLOCK_MERGE_1(front, left, back, right, top, bottom, width, dest) dest = other::BitMapProcess::merge({other::At(front, 0, 0), other::At(left, width, 0), other::At(back, width*2, 0), other::At(right, width*3, 0), other::At(top, width*4, 0), other::At(bottom, width*5, 0)});
#define BLOCK_MERGE(front, width, dest) dest = other::BitMapProcess::merge({other::At(front, 0, 0), other::At(front, width, 0), other::At(front, width*2, 0), other::At(front, width*3, 0), other::At(front, width*4, 0), other::At(front, width*5, 0)});
#define BLOCK_MERGE_HALF(first, second, third, width, dest) dest = other::BitMapProcess::merge({other::At(first, 0, 0), other::At(second, width, 0), other::At(third, width*2, 0)});

#define BLOCK_MAKE_OSMAP(s, s1, o, o1, dest) dest = other::BitMapProcess::channelMerge(s, 0, o, 0, s1, 0, o1, 0);
#define BLOCK_MAKE_NROMALMAP_FULL(front, left, back, right, top, bottom) left = other::BitMapProcess::normalHorizontalRotate(front, true);\
																	back = other::BitMapProcess::normalHorizontalRotate(left, true);\
																	right = other::BitMapProcess::normalHorizontalRotate(back, true);\
																	top = other::BitMapProcess::normalVerticalRotate(front, true);\
																	bottom = other::BitMapProcess::normalVerticalRotate(front, false);

																
namespace global
{
	namespace resource
	{
		namespace texture
		{
			wrapperGL::TextureID TextureMaker::list[static_cast<unsigned int>(TextureName::LAST)];
			std::atomic<unsigned int> TextureMaker::currentProgress;

			void TextureMaker::init() 
			{
				currentProgress.store(0);
			}

			TexturePackage TextureMaker::loadBitMaps(const char* fileName)
			{
				//construct file name
				std::string tName = fileName;
				std::string tPng = ".png";
				std::string tNormal = "_n";
				std::string tSpecular = "_s";
				std::string tOcclusion = "_o";

				using namespace wrapperGL;

				TexturePackage tp;

				ImageObject* img;
				ImageObject* imgN;
				ImageObject* imgO;
				ImageObject* imgS;

				//load texture
				try
				{
					img = GLWrapper::loadImage((BLOCK_PATH + tName + tPng).c_str());
				}
				catch (const std::exception& e)
				{
					//if the texture is not exist, then it makes no sense to load other maps
					//so, just return 
					return tp;
				}

				//load normal map
				try
				{
					imgN = GLWrapper::loadImage((BLOCK_PATH + tName + tNormal + tPng).c_str());
				}
				catch (const std::exception& e)
				{
					imgN = nullptr;
				}

				//load specular map
				try
				{
					imgS = GLWrapper::loadImage((BLOCK_PATH + tName + tSpecular + tPng).c_str());
				}
				catch (const std::exception& e)
				{
					imgS = nullptr;
				}

				//load occlusion
				try
				{
					imgO = GLWrapper::loadImage((BLOCK_PATH + tName + tOcclusion + tPng).c_str());
				}
				catch (const std::exception& e)
				{
					imgO = nullptr;
				}

				tp.texture = img;
				tp.normal = imgN;
				tp.specular = imgS;
				tp.occlusion = imgO;

				return tp;
			}

			void TextureMaker::BlockTopBottomSideLoad(const char* topFileName, const char* sideFileName, const char* bottomFileName, TextureName which, TextureName whichN, TextureName whichOS) 
			{

				ImageObject* dest = nullptr;
				ImageObject* dest1 = nullptr;
				ImageObject* dest2 = nullptr;

				//load side
				auto sideTp = TextureMaker::loadBitMaps(sideFileName);
				if (sideTp.texture == nullptr) 
				{
					throw std::runtime_error("unable to load the texture filename " + std::string(sideFileName));
				}
				int width = sideTp.texture->width;
				//load top
				auto topTp = TextureMaker::loadBitMaps(topFileName);
				if (topTp.texture == nullptr) 
				{
					throw std::runtime_error("unable to load the texture filename " + std::string(topFileName));
				}

				//load bottom
				auto bottomTp = TextureMaker::loadBitMaps(bottomFileName);
				if(bottomTp.texture == nullptr)
				{
					throw std::runtime_error("unable to load the texture filename " + std::string(bottomFileName));
				}

				//make texture
				BLOCK_MERGE_1(sideTp.texture, sideTp.texture, sideTp.texture, sideTp.texture, topTp.texture, bottomTp.texture, width, dest);
				list[static_cast<unsigned int>(which)] = GLWrapper::loadTexture(dest);
				delete sideTp.texture;
				delete topTp.texture;
				delete bottomTp.texture;
				delete dest;
				dest = nullptr;

				//make os
				BLOCK_MAKE_OSMAP(sideTp.specular, sideTp.specular, sideTp.occlusion, sideTp.occlusion, dest);
				BLOCK_MAKE_OSMAP(topTp.specular, bottomTp.specular, topTp.occlusion, bottomTp.occlusion, dest1);
				BLOCK_MERGE_HALF(dest, dest, dest1, width,dest2);
				list[static_cast<unsigned int>(whichOS)] = GLWrapper::loadTexture(dest2);
				delete sideTp.specular;
				delete sideTp.occlusion;
				delete dest;
				delete topTp.specular;
				delete bottomTp.specular;
				delete topTp.occlusion;
				delete bottomTp.occlusion;
				delete dest1;
				delete dest2;
				dest = nullptr;
				dest1 = nullptr;
				dest2 = nullptr;

				//make normal
				ImageObject* left = other::BitMapProcess::normalHorizontalRotate(sideTp.normal, true);
				ImageObject* back = other::BitMapProcess::normalHorizontalRotate(left, true);
				ImageObject* right = other::BitMapProcess::normalHorizontalRotate(back, true);
				ImageObject* top = other::BitMapProcess::normalVerticalRotate(topTp.normal, true);
				ImageObject* bottom = other::BitMapProcess::normalVerticalRotate(bottomTp.normal, false);
				BLOCK_MERGE_1(sideTp.normal, left, back, right, top, bottom, width, dest);
				list[static_cast<unsigned int>(whichN)] = GLWrapper::loadTexture(dest);
				delete sideTp.normal;
				delete left;
				delete back;
				delete right;
				delete top;
				delete bottom;
				delete topTp.normal;
				delete bottomTp.normal;
				delete dest;

				currentProgress+=3;
			}

			void TextureMaker::blockUniformLoad(const char* fileName ,TextureName which, TextureName whichN, TextureName whichOS)
			{
				
				auto tp = TextureMaker::loadBitMaps(fileName);

				if (tp.texture == nullptr) 
				{
					throw std::runtime_error("unable to load the texture filename " + std::string(fileName));
				}
			
				ImageObject* left = nullptr;
				ImageObject* back = nullptr;
				ImageObject* right = nullptr;
				ImageObject* top = nullptr;
				ImageObject* bottom = nullptr;

				ImageObject* dest = nullptr;
				ImageObject* dest1 = nullptr;

				int width = tp.texture->width;
			
				//make texture
				BLOCK_MERGE(tp.texture, width, dest);
				list[static_cast<unsigned int>(which)] = GLWrapper::loadTexture(dest);
				delete tp.texture;
				delete dest;
				dest = nullptr;

				//make os
				BLOCK_MAKE_OSMAP(tp.specular, tp.specular, tp.occlusion, tp.occlusion, dest);
				BLOCK_MERGE_HALF(dest, dest, dest, width, dest1);
				list[static_cast<unsigned int>(whichOS)] = GLWrapper::loadTexture(dest1);
				delete tp.specular;
				delete tp.occlusion;
				delete dest;
				delete dest1;
				dest = nullptr;
				dest1 = nullptr;

				//make normal
				BLOCK_MAKE_NROMALMAP_FULL(tp.normal, left, back, right, top, bottom);
				BLOCK_MERGE_1(tp.normal, left, back, right, top, bottom, width, dest);
				list[static_cast<unsigned int>(whichN)] = GLWrapper::loadTexture(dest);
				delete tp.normal;
				delete left;
				delete back;
				delete right;
				delete top;
				delete bottom;
				delete dest;

				currentProgress+=3;
			}

			const wrapperGL::TextureID& TextureMaker::getTexture(TextureName which) 
			{
				return list[static_cast<unsigned int>(which)];
			}

			float TextureMaker::getLoadingProgress() 
			{
				unsigned int temp = currentProgress.load();
				return (float)temp / static_cast<unsigned int>(TextureName::LAST);
			}

			void TextureMaker::load() 
			{			
				//load stone 
				blockUniformLoad("stone" ,TextureName::STONE, TextureName::STONE_N, TextureName::STONE_OS);

				//load dirt
				blockUniformLoad("dirt", TextureName::DIRT, TextureName::DIRT_N, TextureName::DIRT_OS);

				//load cobble stone
				blockUniformLoad("cobblestone", TextureName::COBBLESTONE, TextureName::COBBLESTONE_N, TextureName::COBBLESTONE_OS);

				//load oak plank
				blockUniformLoad("planks_oak", TextureName::OAK_PLANKS, TextureName::OAK_PLANKS_N, TextureName::OAK_PLANKS_OS);

				//load spruce plank
				blockUniformLoad("planks_spruce", TextureName::SPRUCE_PLANKS, TextureName::SPRUCE_PLANKS_N, TextureName::SPRUCE_PLANKS_OS);

				//load birch plank
				blockUniformLoad("planks_birch", TextureName::BIRCH_PLANKS, TextureName::BIRCH_PLANKS_N, TextureName::BIRCH_PLANKS_OS);

				//load jungle plank
				blockUniformLoad("planks_jungle", TextureName::JUNGLE_PLANKS, TextureName::JUNGLE_PLANKS_N, TextureName::JUNGLE_PLANKS_OS);

				//load acacia plank
				blockUniformLoad("planks_acacia", TextureName::ACACIA_PLANKS, TextureName::ACACIA_PLANKS_N, TextureName::ACACIA_PLANKS_OS);

				//load dark oak plank
				blockUniformLoad("planks_big_oak", TextureName::DARK_OAK_PLANKS, TextureName::DARK_OAK_PLANKS_N, TextureName::DARK_OAK_PLANKS_OS);

				//load bedrock
				blockUniformLoad("bedrock", TextureName::BEDROCK, TextureName::BEDROCK_N, TextureName::BEDROCK_OS);

				//load sand
				blockUniformLoad("sand", TextureName::SAND, TextureName::SAND_N, TextureName::SAND_OS);

				//load grass
				BlockTopBottomSideLoad("grass_top", "grass_side", "grass_bottom", TextureName::GRASS, TextureName::GRASS_N, TextureName::GRASS_OS);

				//load mossy cobblestone
				blockUniformLoad("cobblestone_mossy", TextureName::COBBLESTONE_MOSSY, TextureName::COBBLESTONE_MOSSY_N, TextureName::COBBLESTONE_MOSSY_OS);

				//load still water
				blockUniformLoad("water_still", TextureName::WATER, TextureName::WATER_N, TextureName::WATER_OS);

			}

		}
	}
}