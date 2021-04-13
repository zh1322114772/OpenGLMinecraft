#pragma once
#include <atomic>
#include "GLW_Types.hpp"

using namespace wrapperGL;

namespace global
{
	namespace resource
	{
		namespace mesh
		{
			class MeshMaker final 
			{
			public:
				enum class MeshType 
				{
					CUBE,
					CUBES,
					WATER_TOP_CUBES,
					HUMAN,

					LAST,
				};

				/// <summary>
				/// load all meshes
				/// </summary>
				static void load();

				/// <summary>
				/// get particular mesh
				/// </summary>
				/// <param name="which"></param>
				/// <returns></returns>
				static const wrapperGL::VAOID* getMesh(MeshType which);

				/// <summary>
				/// get loading progress
				/// </summary>
				/// <returns></returns>
				static float getLoadingProgress();

				static void init();

			private:
				static std::atomic<unsigned int> currentProgress;
				
				static wrapperGL::VAOID list[static_cast<unsigned int>(MeshType::LAST)];
			};

		}

	}
}