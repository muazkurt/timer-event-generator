#ifndef GUARD_H
	#define GUARD_H
	#include <thread>
	#include <mutex>
	#include <functional>
	namespace MuazKurt
	{
		class Timer;
		class ThreadGuard
		{
		public:
			ThreadGuard(){}
			void init(std::function<void(Timer *)> func, Timer * const aTimer);
			~ThreadGuard();
			ThreadGuard(ThreadGuard &) = delete;
			ThreadGuard & operator=(ThreadGuard&) = delete;
		private:
			std::thread myThread;
		};
	} // namespace MuazKurt
#endif
