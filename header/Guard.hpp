#include <thread>
#include <mutex>
namespace MuazKurt
{
	class ThreadGuard
	{
	public:
		ThreadGuard(){}
		void init(std::thread &&t);
		~ThreadGuard();
		ThreadGuard(ThreadGuard &) = delete;
		ThreadGuard &operator=(ThreadGuard&) = delete;
	private:
		std::thread myThread;
	};
} // namespace MuazKurt
