#pragma once
#include "TickClock_Types.hpp"
#include "GLW_GlmHeaders.hpp"
#include <atomic>
namespace tickerable 
{
	namespace tasks 
	{
		/// <summary>
		/// thread safety vector 3
		/// </summary>
		namespace inputGetterTypes 
		{
			template<typename t>
			struct AtomicVec3
			{
				std::atomic<t> x;

				std::atomic<t> y;

				std::atomic<t> z;
			};
		
			template<typename t>
			struct Vec3 
			{
				t x;
				t y;
				t z;
			};
		
		}


		/// <summary>
		/// this class deliver all necessary inputs from main render thread to tick-Clock thread
		/// </summary>
		class InputGetter : public tickerable::Task
		{
		private:
			/// <summary>
			/// current camera view
			/// </summary>
			inputGetterTypes::AtomicVec3<float> aView;
			inputGetterTypes::Vec3<float> view;

			/// <summary>
			/// current movement direction
			/// </summary>
			inputGetterTypes::AtomicVec3<float> aDirection;
			inputGetterTypes::Vec3<float> direction;

			/// <summary>
			/// current position
			/// </summary>
			inputGetterTypes::AtomicVec3<double> aPosition;
			inputGetterTypes::Vec3<double> position;

		public:
			/// <summary>
			/// current camera view direction
			/// </summary>
			/// <param name="v">view direction</param>
			void setView(glm::vec3 v);

			/// <summary>
			/// get current camera view
			/// </summary>
			/// <returns>view vector</returns>
			const inputGetterTypes::Vec3<float>& getView();

			/// <summary>
			/// set current movement direction
			/// </summary>
			/// <param name="v"></param>
			void setDirection(glm::vec3 v);

			/// <summary>
			/// set current position
			/// </summary>
			/// <param name="x">x position</param>
			/// <param name="y">y position</param>
			/// <param name="z">z position</param>
			void setPosition(double x, double y, double z);

			/// <summary>
			/// get current position
			/// </summary>
			/// <returns></returns>
			const inputGetterTypes::Vec3<double>& getPosition();

			/// <summary>
			/// get current movement direction
			/// </summary>
			/// <returns></returns>
			const inputGetterTypes::Vec3<float>& getDirection();

			void onEnable() override;

			void onDisable() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;
		
		};
	
	
	
	}

}