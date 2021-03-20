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
				/// chunk generation time
				/// </summary>
				long long timeStamp = 0;

				/// <summary>
				/// chunk ID
				/// </summary>
				unsigned int chunkID = 0;

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
			/// shows where the chunk should be loaded and recycled
			/// </summary>
			bool chunkRegionMap[(MAX_RADIUS * 2) + 1][(MAX_RADIUS * 2) + 1];

			/// <summary>
			/// shows which region is loaded
			/// </summary>
			bool chunkLoadingMap[(MAX_RADIUS * 2) + 1][(MAX_RADIUS * 2) + 1];
			
			/// <summary>
			/// shows where the loaded chunks are located at
			/// </summary>
			chunkLoaderTypes::Chunk* chunkPositionMap[(MAX_RADIUS * 2) + 1][(MAX_RADIUS * 2) + 1];

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
			
			/// <summary>
			/// hide chunk inner invisible blocks
			/// </summary>
			/// <param name="chunk">chunk Pointer</param>
			/// <param name="x">position map x location</param>
			/// <param name="y">position map y location</param>
			void hideBlocks(chunkLoaderTypes::Chunk* chunk, long long x, long long y);




			/// <summary>
			/// convert two values into one
			/// </summary>
			/// <param name="x">value 0</param>
			/// <param name="y">value 1</param>
			/// <returns></returns>
			inline long long XYtoX(long long x, long long y);

			/// <summary>
			/// get similarity value by surrounding 4 points
			/// </summary>
			/// <param name="seed">random seed</param>
			/// <param name="topLeftX">point top left x</param>
			/// <param name="topLeftY">point top left y</param>
			/// <param name="size">surrounding point width & height</param>
			/// <param name="currentX">current point x</param>
			/// <param name="currentY">current point y</param>
			/// <returns></returns>
			inline float getSimilarityMix(unsigned long long seed, float topLeftX, float topLeftY, float size, float flatness, float currentX, float currentY);

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

			/// <summary>
			/// get active chunk list
			/// </summary>
			/// <returns></returns>
			const std::vector<chunkLoaderTypes::Chunk*>& getActiveList();

			void onEnable() override;

			void onDisable() override;

			void onExit() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;
		
		
		};

	}
}