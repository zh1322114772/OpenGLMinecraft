#pragma once
#include "CFG_BLOCKS.hpp"
#include "TickClock_Types.hpp"
#include <queue>
#include <limits>

#define MAX_RADIUS 64

namespace tickerable
{
	namespace tasks
	{
		namespace chunkLoaderTypes 
		{

			struct Chunk 
			{

				/// <summary>
				/// if chunk is in active list
				/// </summary>
				bool isActive = false;

				/// <summary>
				/// chunk world location
				/// </summary>
				long long locationX = LLONG_MAX, locationY = LLONG_MAX;

				/// <summary>
				/// chunk data y, x, z
				/// </summary>
				game::config::blocks::Block blocks[256][16][16] = {game::config::blocks::AirBlock()};

				/// <summary>
				/// visible states for every block in a chunk
				/// </summary>
				bool blockVisible[256][16][16] = { false };

			};

		}

		class ChunkLoader : public Task
		{
		private:
			const int viewDistance;
			/// <summary>
			/// total chunks
			/// </summary>
			chunkLoaderTypes::Chunk** chunkList;

			/// <summary>
			/// in use chunks
			/// </summary>
			std::vector<chunkLoaderTypes::Chunk*> activeChunkList;

			/// <summary>
			/// recycled chunks
			/// </summary>
			std::queue<chunkLoaderTypes::Chunk*> recycleList;

			/// <summary>
			/// total chunks
			/// </summary>
			int chunkListSize;

			/// <summary>
			/// template that represents where the chunk should be loaded and recycled
			/// </summary>
			bool chunkLoadRegion[(MAX_RADIUS * 2) + 1][(MAX_RADIUS * 2) + 1];

			/// <summary>
			/// mask that represents where the loaded chunks are located at
			/// </summary>
			bool chunkLoadedMask[(MAX_RADIUS * 2) + 1][(MAX_RADIUS * 2) + 1];

			/// <summary>
			/// boundaries of chunkLoadRegion template
			/// </summary>
			unsigned short int leftTop, rightBottom;

			/// <summary>
			/// world random seed
			/// </summary>
			unsigned long long seed;

			/// <summary>
			/// generate terrain in chunk
			/// </summary>
			/// <param name="chunk">chunk pointer</param>
			void genChunkData(chunkLoaderTypes::Chunk* chunk);

		public:
			/// <summary>
			/// constructor
			/// </summary>
			/// <param name="v"> view distance </param>
			/// <param name="seed"> world seed </param>
			/// <returns></returns>
			ChunkLoader(const int v, unsigned long long seed);

			~ChunkLoader();

			/// <summary>
			/// get chunk list
			/// </summary>
			/// <returns></returns>
			chunkLoaderTypes::Chunk** getChunkList();

			/// <summary>
			/// size of chunk list
			/// </summary>
			/// <returns></returns>
			int getChunkListSize();



			void onEnable() override;

			void onDisable() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;
		
		
		};

	}
}