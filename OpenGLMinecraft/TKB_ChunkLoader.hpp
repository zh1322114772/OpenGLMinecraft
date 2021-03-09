#pragma once
#include "CFG_BLOCKS.hpp"
#include <atomic>
#include "TickClock_Types.hpp"
#include <queue>
#include <limits>
namespace tickerable
{
	namespace tasks
	{
		namespace chunkLoaderTypes 
		{
			struct Chunk 
			{
				/// <summary>
				/// chunk world location
				/// </summary>
				long long locationX = LLONG_MAX, locationY = LLONG_MAX;

				/// <summary>
				/// current chunk status 
				/// </summary>
				std::atomic<bool> isLoading = true;

				/// <summary>
				/// chunk data y, x, z
				/// </summary>
				game::config::blocks::Block blocks[256][16][16];
				
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
			std::vector<chunkLoaderTypes::Chunk*> ativeList;

			/// <summary>
			/// recycled chunks
			/// </summary>
			std::queue<chunkLoaderTypes::Chunk*> recycleList;

			/// <summary>
			/// maximum radius of 64, used to check if a chunk should be loaded or recycled
			/// </summary>
			bool chunkRegionMask[129][129] = {false};

			/// <summary>
			/// total chunks
			/// </summary>
			int chunkListSize;

			/// <summary>
			/// generate terrain in chunk
			/// </summary>
			/// <param name="chunk">chunk pointer</param>
			/// <param name="locX">chunk x location</param>
			/// <param name="locY">chunk y location</param>
			inline void genChunkData(chunkLoaderTypes::Chunk* chunk, long long locX, long long locY);

		public:
			/// <summary>
			/// constructor
			/// </summary>
			/// <param name="v"> view distance </param>
			/// <returns></returns>
			ChunkLoader(const int v);

			~ChunkLoader();

			void onEnable() override;

			void onDisable() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;
		
		
		};

	}
}