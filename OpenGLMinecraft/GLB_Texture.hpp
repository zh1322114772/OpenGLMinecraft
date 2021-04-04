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
			class TextureMaker final
			{
			public:
				enum class TextureName
				{
					STONE,
					STONE_N,
					STONE_O,
					STONE_S,

					DIRT,
					DIRT_N,
					DIRT_O,
					DIRT_S,

					COBBLESTONE,
					COBBLESTONE_N,
					COBBLESTONE_O,
					COBBLESTONE_S,

					OAK_PLANKS,
					OAK_PLANKS_N,
					OAK_PLANES_O,
					OAK_PLANES_S,

					SPRUCE_PLANKS,
					SPRUCE_PLANKS_N,
					SPRUCE_PLANKS_O,
					SPRUCE_PLANKS_S,

					BRICH_PLANKS,
					BRICH_PLANKS_N,
					BRICH_PLANKS_O,
					BRICH_PLANKS_S,

					JUNGLE_PLANKS,
					JUNGLE_PLANKS_N,
					JUNGLE_PLANKS_O,
					JUNGLE_PLANKS_S,

					ACACIA_PLANKS,
					ACACIA_PLANKS_N,
					ACACIA_PLANKS_O,
					ACACIA_PLANKS_S,

					DARK_OAK_PLANKS,
					DARK_OAK_PLANKS_N,
					DARK_OAK_PLANKS_O,
					DARK_OAK_PLANKS_S,

					BEDROCK,
					BEDROCK_N,
					BEDROCK_O,
					BEDROCK_S,

					SAND,
					SAND_N,
					SAND_O,
					SAND_S,

					GRASS,
					GRASS_N,
					GRASS_O,
					GRASS_S,

					COBBLESTONE_MOSSY,
					COBBLESTONE_MOSSY_N,
					COBBLESTONE_MOSSY_O,
					COBBLESTONE_MOSSY_S,

					WATER,
					WATER_N,
					WATER_O,
					WATER_S,

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
				/// get total textures
				/// </summary>
				/// <returns></returns>
				static unsigned int& getTotalTextureCount();

				/// <summary>
				/// get loading progress
				/// </summary>
				/// <returns></returns>
				static unsigned int getLoadingProgress();

				static void init();

			private:
				static wrapperGL::TextureID list[static_cast<unsigned int>(TextureName::LAST)];

				static std::atomic<unsigned int> currentProgress;

			};


		}

	}
}
