#pragma once

#include "Render_Types.hpp"
#include "GLW_GLShader.hpp"
#include "GLW_Types.hpp"
#include <memory>
#include <iostream>
#include "WorldTickClock.hpp"
#include "TKB_ChunkLoader.hpp"
#include "CLR_World3DTypes.hpp"

#include "GLB_Block.hpp"
#include "GLB_Entity.hpp"

namespace renderer
{

	namespace controllers
	{

		class World3D : public Controller
		{
		private:
			//shader programs
			wrapperGL::ShaderProgram* blockShader;
			wrapperGL::ShaderProgram* entityShader;

			double secondCounter = 0;
			
			//for terrain render
			std::vector<std::tuple<unsigned int*, int, global::resource::block::BlockRenderInfo*, float, float>> normalBlockList;
			std::vector<std::tuple<unsigned int*, int, global::resource::block::BlockRenderInfo*, float, float>> liquidBlockList;

			//view
			glm::mat4 projectionMatrix;
			world3DTypes::Camera camera;
			glm::vec2 mousePos;
			
			//event updater
			tickerable::WorldTickClock* tickClock;

			/// <summary>
			/// draw chunks
			/// </summary>
			inline void terrainDrawer();

			/// <summary>
			/// draw entites
			/// </summary>
			inline void entityDrawer();

			//test purpose
			global::resource::entity::Human* testHuman;

		public:
			/// <summary>
			/// constructor
			/// </summary>
			/// <param name="clock">tick clock to update events</param>
			/// <returns></returns>
			World3D(tickerable::WorldTickClock* clock);
			
			/// <summary>
			/// set current camera
			/// </summary>
			/// <param name="cam">camera object</param>
			void setCamera(world3DTypes::Camera& cam);

			/// <summary>
			/// set new projection matrix
			/// </summary>
			/// <param name="projection">projection matrix</param>
			void setProjection(glm::mat4& projection);

			/// <summary>
			/// draw blocks
			/// </summary>
			/// <param name="infoArr">chunk buffer block sequence</param>
			/// <param name="size">block sequence size</param>
			/// <param name="m">the block to be drawn</param>
			/// <param name="s">shader program</param>
			inline void blockDrawer(unsigned int* infoArr, int size, global::resource::block::BlockRenderInfo* m, wrapperGL::ShaderProgram* s);


			//inherited from Controller

			void onStart() override;

			void onExit() override;

			void onEnable() override;

			void onDisable() override;

			void onDraw(const double& delta_t) override;

			void renderAreaChangedCallback(const int& newWidth, const int& newHeight) override;

			void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t) override;

		};

	}
}