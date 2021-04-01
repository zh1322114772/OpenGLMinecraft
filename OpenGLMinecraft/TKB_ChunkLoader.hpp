#pragma once
#include "TickClock_Types.hpp"
#include "GLB_Resources.hpp"
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
				/// last change time
				/// </summary>
				long long updateTime = 0;

				/// <summary>
				/// chunk world location
				/// </summary>
				long long locationX = LLONG_MAX, locationY = LLONG_MAX;

				/// <summary>
				/// chunk data y, x, z
				/// </summary>
				global::resource::blocks::Block blocks[256][16][16] = {global::resource::blocks::AirBlock()};

				/// <summary>
				/// visible states for every block in a chunk
				/// use first 6 bits to represents the visible state for 6 faces 
				/// 0 = visible
				/// 1 = invisible
				/// </summary>
				unsigned char blockVisibleState[256][16][16] = { 0b111111 };

				/// <summary>
				/// count how many of each different types of block in a chunk
				/// </summary>
				unsigned short int blockCounter[CFG_BLOCKMESH_ID_LAST];

				/// <summary>
				/// true if current chunk is located on the edge
				/// </summary>
				bool edge = false;
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
			/// map loaded chunks to corresponding index
			/// </summary>
			chunkLoaderTypes::Chunk* chunkLoadingMap[(MAX_RADIUS * 2) + 1][(MAX_RADIUS * 2) + 1];

			/// <summary>
			/// chunks located on the edge
			/// </summary>
			std::vector<chunkLoaderTypes::Chunk*> edgeList;

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
			/// <param name="samplingRange">point sampling range, </param>
			/// <param name="blockX">current block x position in the chunk</param>
			/// <param name="blockZ">current block z position in the chunk</param>
			/// <param name="select">specify the percentage that outputs nonzero result</param>
			/// <param name="select">specify the bias to be added to the sampling points</param>
			/// <returns></returns>
			inline std::tuple<float, glm::vec4, glm::vec4> getSimilarityMix(unsigned long long seed, float topLeftX, float topLeftY, float flatness, int samplingRange, float blockX, float blockZ, float select = 1.0, glm::vec4 selectBias = glm::vec4(0.0));

			/// <summary>
			/// generate a list of blocks that will be filled into the chunk
			/// </summary>
			/// <param name="info">info array</param>
			/// <param name="counter">info length</param>
			/// <param name="chunkX">current chunk x</param>
			/// <param name="chunkY">current chunk y</param>
			/// <param name="x">x position in the chunk</param>
			/// <param name="z">z position in the chunk</param>
			inline void verticalInfoGenerator(std::tuple<int, int, global::resource::blocks::Block>* info, int& counter, long long chunkX, long long chunkY, int x, int z);

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