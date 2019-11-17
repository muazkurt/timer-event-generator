#include "../header/Guard.hpp"
void MuazKurt::ThreadGuard::init(std::function<void(MuazKurt::Timer * const)> func, MuazKurt::Timer * const aTimer)
{
	myThread = std::thread(func, aTimer);
}

MuazKurt::ThreadGuard::~ThreadGuard()
{
	if (myThread.joinable())
		myThread.join();
}