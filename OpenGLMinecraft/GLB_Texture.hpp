#pragma once
#include "GLW_Types.hpp"
#include <string>
#include <atomic>
namespace global
{
	namespace resource
	{
		namespace texture
		{
			struct TexturePackage 
			{
				wrapperGL::ImageObject* texture = nullptr;
				wrapperGL::ImageObject* normal = nullptr;
				wrapperGL::ImageObject* specular = nullptr;
				wrapperGL::ImageObject* occlusion = nullptr;
			};

			class TextureMaker final
			{
			public:
				enum class TextureName
				{
					STONE,
					STONE_N,
					STONE_OS,

					DIRT,
					DIRT_N,
					DIRT_OS,

					COBBLESTONE,
					COBBLESTONE_N,
					COBBLESTONE_OS,

					OAK_PLANKS,
					OAK_PLANKS_N,
					OAK_PLANKS_OS,

					SPRUCE_PLANKS,
					SPRUCE_PLANKS_N,
					SPRUCE_PLANKS_OS,

					BIRCH_PLANKS,
					BIRCH_PLANKS_N,
					BIRCH_PLANKS_OS,

					JUNGLE_PLANKS,
					JUNGLE_PLANKS_N,
					JUNGLE_PLANKS_OS,

					ACACIA_PLANKS,
					ACACIA_PLANKS_N,
					ACACIA_PLANKS_OS,

					DARK_OAK_PLANKS,
					DARK_OAK_PLANKS_N,
					DARK_OAK_PLANKS_OS,

					BEDROCK,
					BEDROCK_N,
					BEDROCK_OS,

					SAND,
					SAND_N,
					SAND_OS,

					GRASS,
					GRASS_N,
					GRASS_OS,

					COBBLESTONE_MOSSY,
					COBBLESTONE_MOSSY_N,
					COBBLESTONE_MOSSY_OS,

					WATER,
					WATER_N,
					WATER_OS,

					LAST
				};

				/// <summary>
				/// load all textures
				/// </summary>
				static void load();

				/// <summary>
				/// get particular texture id
				/// </summary>
				/// <param name="which"></param>
				/// <returns></returns>
				static const wrapperGL::TextureID& getTexture(TextureName which);

				/// <summary>
				/// get loading progress
				/// </summary>
				/// <returns></returns>
				static float getLoadingProgress();

				static void init();

			private:
				static wrapperGL::TextureID list[static_cast<unsigned int>(TextureName::LAST)];

				static std::atomic<unsigned int> currentProgress;

				/// load simple block texture format
				/// </summary>
				/// <param name="fileName">texture file name</param>
				/// <param name="which">corresponding block texture id</param>
				/// <param name="whichN">corresponding block normal id</param>
				/// <param name="whichOS">corresponding block specular and occlusion id</param>
				static inline void blockUniformLoad(const char* fileName, TextureName which, TextureName whichN, TextureName whichOS);

				/// load block texture with top, bottom, side format
				/// </summary>
				/// <param name="topFileName">top texture file name</param>
				/// <param name="sideFileName">side texture file name</param>
				/// <param name="bottomFileName">bottom texture file name</param>
				/// <param name="which">corresponding block texture id</param>
				/// <param name="whichN">corresponding block normal id</param>
				/// <param name="whichOS">corresponding block specular and occlusion id</param>
				static inline void BlockTopBottomSideLoad(const char* topFileName, const char* sideFileName, const char* bottomFileName, TextureName which, TextureName whichN, TextureName whichOS);

				/// <summary>
				/// load texture, nromal, specular and occlusion maps
				/// </summary>
				/// <param name="fileName">file name</param>
				/// <returns></returns>
				static TexturePackage loadBitMaps(const char* fileName);

			};


		}

	}
}
