#pragma once
#include <vector>

namespace tickerable
{
	/// <summary>
	/// the task for TickClock
	/// </summary>
	class Task 
	{
	public:
		/// <summary>
		/// this function will be called after TickClock.start()
		/// </summary>
		virtual void onEnable() = 0;
		
		/// <summary>
		/// this function will be called after TickClock.stop()
		/// </summary>
		virtual void onDisable() = 0;

		/// <summary>
		/// this function will be called on every tick
		/// </summary>
		/// <param name="delta_t">time intervals between two ticks</param>
		/// <param name="taskList">task list</param>
		virtual void Tick(const double& delta_t, const std::vector<Task*>& taskList) = 0;
	};


}