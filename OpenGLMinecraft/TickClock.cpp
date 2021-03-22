#include "TickClock.hpp"
#include <stdexcept>
#include <chrono>
#include <iostream>
namespace tickerable 
{
	TickClock::TickClock(const float interval):tick(interval)
	{
		status = STOPPED;
	}

	void TickClock::addTask(Task* task) 
	{
		if (status == STOPPED) 
		{
			taskList.push_back(task);
		}
		else 
		{
			throw std::runtime_error("Unable to add new task while running");
		}
		
	}

	void TickClock::pause() 
	{
		if (status == RUNNING) 
		{
			status = PAUSING;
			while (status == PAUSING) 
			{
				//wait till thread paused
			}

		}
		else 
		{
			throw std::runtime_error("Tick clock is not running, unable to pause.");
		}
	
	}

	void TickClock::stop() 
	{
		if (status == RUNNING || status == PAUSED)
		{
			status = STOPPING;
			while (status == STOPPING)
			{
				//wait till thread stop
			}
			
		}
		else 
		{
			throw std::runtime_error("Tick clock is not running, unable to stop");
		}
	
	}

	TickClock::~TickClock() 
	{
		for (auto i = taskList.begin(); i < taskList.end(); i++)
		{
			(*i)->onExit();
		}
	}

	void TickClock::resume() 
	{
		if (status == PAUSED) 
		{
			status = RUNNING;
		}
		else 
		{
			throw std::runtime_error("Tick clock is not paused, unable to resume");
		}
	}

	void TickClock::start() 
	{
		if (status == STOPPED) 
		{
			status = RUNNING;
			tickThread = std::thread(&TickClock::run, this);
			tickThread.detach();
		}
		else 
		{
			throw std::runtime_error("Tick clock is running, unable to start");
		}
	}

	void TickClock::run()
	{
		//init all tasks
		for (auto i = taskList.begin(); i < taskList.end(); i++) 
		{
			(*i)->onEnable();
		}

		double milliTime = 0;
		double milliTime1 = 0;
		double delta_t = 0;
		using namespace std::chrono;
		while (status != STOPPING) 
		{

			if (status == RUNNING) 
			{

				milliTime = (double)(duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count()) / 1000.0;
				//tick all tasks
				for (auto i = taskList.begin(); i < taskList.end(); i++)
				{
					(*i)->Tick(delta_t, taskList);
				}
				milliTime1 = (double)(duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count()) / 1000.0;

				//get delta t
				delta_t = milliTime1 - milliTime;

				//sleep till desire tick time
				int remainTime = (int)(tick - delta_t);
				if (remainTime > 0) 
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(remainTime));
				}
			
			}
			else if (status == PAUSING)
			{
				status = PAUSED;
			}

		}

		//exit all tasks
		for (auto i = taskList.begin(); i < taskList.end(); i++)
		{
			(*i)->onDisable();
		}
		
		//set state to stopped
		status = STOPPED;
	}
}