#pragma once

#include "Render_Types.hpp"
#include "GLW_GLShader.hpp"
#include "CLR_World3D_Types.hpp"
#include "GLW_Types.hpp"
#include <memory>
#include <iostream>
#include "WorldTickClock.hpp"
#include "TKB_ChunkLoader.hpp"

namespace renderer
{

	namespace controllers
	{

		class World3D : public Controller
		{
		private:
			//current shader program
			std::shared_ptr<wrapperGL::ShaderProgram> shader;

			//view
			glm::mat4 projectionMatrix;
			world3D::Camera camera;
			glm::vec2 mousePos;
			
			//event updater
			tickerable::WorldTickClock* tickClock;

			//test purpose
			wrapperGL::VAOID blockVID;
			wrapperGL::VAOList* blockV;

			/// <summary>
			/// draw chunks
			/// </summary>
			inline void terrainDrawer();

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
			void setCamera(world3D::Camera& cam);

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
			inline void blockDrawer(unsigned int* infoArr, int size, world3D::BlockMesh* m);


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