#pragma once
#include "TickClock_Types.hpp"
#include <vector>
#include <atomic>
#include <thread>
namespace tickerable
{
	/// <summary>
	/// this clock class 
	/// </summary>
	class TickClock 
	{
	private:
		//status tags
		const char RUNNING = 0;
		const char STOPPED = 1;
		const char PAUSED = 2;
		const char STOPPING = 3;
		const char PAUSING = 4;

		//current status
		std::atomic<char> status;

		//task list
		std::vector<Task*> taskList;

		//tick thread
		std::thread tickThread;
	private:

		void run();

	public:
		const double tick;

		/// <summary>
		/// constructor
		/// </summary>
		/// <param name="interval">interval in millisecond</param>
		/// <returns></returns>
		TickClock(const float interval);
	
		/// <summary>
		/// add the task to tick clock
		/// </summary>
		/// <param name="task">task</param>
		void addTask(Task* task);

		/// <summary>
		/// start the tick clock
		/// </summary>
		void start();

		/// <summary>
		/// stop the tick clock
		/// </summary>
		void stop();

		/// <summary>
		/// resume the tick clock
		/// </summary>
		void resume();

		/// <summary>
		/// pause the tick clock
		/// </summary>
		void pause();
	};
}