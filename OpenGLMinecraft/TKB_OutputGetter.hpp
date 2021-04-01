#pragma once
#include "TickClock_Types.hpp"
#include "TKB_ChunkLoader.hpp"
#include "GLB_Resources.hpp"
#include <limits>

namespace tickerable
{
	namespace tasks
	{
		namespace outputGetterTypes
		{
			union BlockInfo 
			{
				struct PosData
				{
					unsigned char axisXZ;
					unsigned char invisibleFaces;
					unsigned short int axisY;

				}posData;

				unsigned int data;
			};

			struct ChunkBuffer 
			{
				
				/// <summary>
				/// every unsigned int stores block position info
				/// bit 0 - 4: z axis
				/// bit 4 - 8: x axis
				/// bit 8 - 16: invisible faces
				/// bit 16 - 32: y axis
				/// </summary>
				BlockInfo blockSequence[65536] = { 0 };

				/// <summary>
				/// count how many of each different types of block in a chunk
				/// </summary>
				unsigned short int blockCounter[CFG_BLOCKMESH_ID_LAST] = { 0 };

				/// <summary>
				/// chunk world location
				/// </summary>
				long long locationX = LLONG_MAX, locationY = LLONG_MAX;

				/// <summary>
				/// chunk update time
				/// </summary>
				long long updateTime = 0;

				/// <summary>
				/// wether a chunk buffer should be rendered or not
				/// </summary>
				bool isActive = false;

			};


		}


		/// <summary>
		/// this class deliver all necessary data from tick-Clock to main render thread
		/// </summary>
		class OutputGetter : public Task
		{
		private:

			/// <summary>
			/// total chunk buffers
			/// </summary>
			outputGetterTypes::ChunkBuffer** chunkBuffers;

			/// <summary>
			/// chunk render buffer size
			/// </summary>
			int chunkBufferSize;

			/// <summary>
			/// process chunk data to chunk buffer
			/// </summary>
			/// <param name="chunkBuffer">chunk buffer</param>
			/// <param name="chunkData">chunk data</param>
			void chunkData2ChunkBuffer(outputGetterTypes::ChunkBuffer* chunkBuffer, tasks::chunkLoaderTypes::Chunk* chunkData);

		public:
			/// <summary>
			/// constructor
			/// </summary>
			/// <param name="viewDistance">chunk loading radius</param>
			/// <returns></returns>
			OutputGetter(const int viewDistance);

			/// <summary>
			/// get chunk buffer size
			/// </summary>
			/// <returns></returns>
			int getChunkBufferSize();

			/// <summary>
			/// get chunk buffer
			/// </summary>
			/// <returns></returns>
			outputGetterTypes::ChunkBuffer** getChunkBuffers();

			void onEnable() override;

			void onDisable() override;

			void onExit() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;

		};


	}

}