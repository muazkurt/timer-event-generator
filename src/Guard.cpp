#include "../header/Guard.hpp"
void MuazKurt::ThreadGuard::init(std::thread &&t)
{
	myThread = std::thread(std::move(t));
}

MuazKurt::ThreadGuard::~ThreadGuard()
{
	if (myThread.joinable())
		myThread.join();
}