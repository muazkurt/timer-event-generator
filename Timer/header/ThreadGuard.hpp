#ifndef GUARD_H
	#define GUARD_H
	#include <thread>
	#include <functional>
	namespace MuazKurt
	{
		class Timer;
		/**
		 * This is a class to save a thread to die alone.
		 **/
		class ThreadGuard
		{
		public:
			/**
			 * Does nothing, because main job delegated to init function.
			 **/
			ThreadGuard(){}
			/**
			 * Creates the owned thread to do given job on Timer * object.
			 **/
			void init(std::function<void(Timer *)> func, Timer * const aTimer);
			/**
			 * Cleans the thread and its all data. Exits safely.
			 **/
			~ThreadGuard();
			ThreadGuard(ThreadGuard &) = delete;
			ThreadGuard & operator=(ThreadGuard&) = delete;
		private:
			std::thread myThread;
		};
	} // namespace MuazKurt
#endif
