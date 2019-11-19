#include "../header/Timer.hpp"
#include <iostream>

bool MuazKurt::Timer::item_exist = false;

MuazKurt::Timer::Timer() : queueSaver(), eventQueue()
{
	item_exist = true;
	timer.init(MuazKurt::theJob, this);
}
MuazKurt::Timer::~Timer()
{
	item_exist = false;
}
void MuazKurt::Timer::enqueueEvent(const MuazKurt::Timer::Event & enqueable)
{
	std::lock_guard<std::mutex> lg(queueSaver);
	eventQueue.push(enqueable);
}

void MuazKurt::Timer::one_job() 
{
	MuazKurt::Timer::Event	next;
	bool					possible = false;
	{
		std::lock_guard<std::mutex> lg(queueSaver);
		next = eventQueue.top();
		if((possible = (next.next_work - CLOCK::now()).count()) < std::chrono::duration_cast<CLOCK::duration>(Millisecs(4)).count())
			eventQueue.pop();
	}
	if(possible && next.doit())
	{
		std::cout << "Job is done with " << abs(std::chrono::duration_cast<Millisecs>(next.next_work - CLOCK::now()).count()) << " milisecs interval." << std::endl; 
		next.next_work = next.period + CLOCK::now();
		enqueueEvent(next);
	}
}

bool MuazKurt::Timer::isEmpty()
{
	return eventQueue.empty();
}

bool MuazKurt::Timer::alive()
{
	return item_exist;
}

void MuazKurt::Timer::registerTimer(const Timepoint &tp, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("time point", tp, Millisecs::min(), [](){return true;}, callback));
}

void MuazKurt::Timer::registerTimer(const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("period", CLOCK::now(), period, [](){return true;}, callback));
}

void MuazKurt::Timer::registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("timepoint + period", CLOCK::now(), period,
		[tp](){return ((tp - CLOCK::now()).count() > 0);}, callback));
}

void MuazKurt::Timer::registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("predicate + period", CLOCK::now(), period, pred, callback));
}
