#include "../header/Timer.hpp"
#include <iostream>

MuazKurt::Timer::Timer() : queueSaver(), eventQueue()
{
	timer.init(std::thread(MuazKurt::theJob, this));
}

void MuazKurt::Timer::enqueueEvent(const MuazKurt::Timer::Event & enqueable)
{
	std::lock_guard<std::mutex> lg(queueSaver);
	eventQueue.push(enqueable);
}

const MuazKurt::Timer::Event & MuazKurt::Timer::peek() 
{
	std::lock_guard<std::mutex> lg(queueSaver);
	return eventQueue.top();
}

const void MuazKurt::Timer::dequeue()
{
	std::lock_guard<std::mutex> lg(queueSaver);
	eventQueue.pop();
}

bool MuazKurt::Timer::isEmpty()
{
	std::lock_guard<std::mutex> lg(queueSaver);
	return eventQueue.size() < 1;
}

void MuazKurt::Timer::registerTimer(const Timepoint &tp, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("time point", tp, Millisecs::min(), [](){return true;}, callback));
}

void MuazKurt::Timer::registerTimer(const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("period", CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(period), period, [](){return true;}, callback));
}

void MuazKurt::Timer::registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("timepoint + period", tp + std::chrono::duration_cast<CLOCK::duration>(period), period, [](){return true;}, callback));
}

void MuazKurt::Timer::registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("predicate + period", CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(period), period, pred, callback));
}

bool MuazKurt::Timer::Event::doit()
{
	bool _periodic = (period != Millisecs::min());
	if(predicate())
		callback();
	else _periodic = false;
	return _periodic;
}

bool MuazKurt::Timer::Event::operator <(const MuazKurt::Timer::Event& a) 
{
	return next_work > a.next_work;
}

bool MuazKurt::operator <(const MuazKurt::Timer::Event& a, const MuazKurt::Timer::Event& b)
{
	return a < b;
}

void MuazKurt::theJob(MuazKurt::Timer * timerObject)
{
	while(true)
	{
		if(!timerObject->isEmpty())
		{
			auto next = timerObject->peek();
			auto s = CLOCK::now();
			std::cerr << "name " << next.get_name() << std::endl;
			std::cerr << "nw " << next.get_next_work().time_since_epoch().count() << std::endl;
			std::cerr << "curr " << s.time_since_epoch().count() << std::endl;
			std::cerr << "diff " << (next.get_next_work() - s).count() << std::endl;
			std::cerr << "msec " << std::chrono::duration_cast<CLOCK::duration>(Millisecs(2)).count() << std::endl;
			getc(stdin);
			if(next.get_next_work() - CLOCK::now() < std::chrono::duration_cast<CLOCK::duration>(std::chrono::microseconds(2)))
			{
				std::cout << (next.get_next_work() - CLOCK::now()).count() << std::endl;
				timerObject->dequeue();
				if(next.doit())
					timerObject->enqueueEvent(next);
			}
		}
	}
}