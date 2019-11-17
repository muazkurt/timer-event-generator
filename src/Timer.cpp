#include "../header/Timer.hpp"
#include <iostream>

bool MuazKurt::Timer::item_exist = false;

MuazKurt::Timer::Timer() : queueSaver(), eventQueue()//, age_timer(CLOCK::now().time_since_epoch().count() + AGE_MILISEC)
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
	//age_once();
	std::cerr << "push" << std::endl;
	eventQueue.push(enqueable);
}

void MuazKurt::Timer::one_job() 
{
	MuazKurt::Timer::Event	next;
	bool					possible = false;
	{
		std::lock_guard<std::mutex> lg(queueSaver);
		next = eventQueue.top();
		if((possible = (next.next_work - CLOCK::now()).count() < std::chrono::duration_cast<CLOCK::duration>(std::chrono::microseconds(300)).count()))
		{
			std::cerr << "pop" << std::endl;
			eventQueue.pop();
		}
	}
	if(possible && next.doit())
	{
		next.next_work = next.period + CLOCK::now();
		//age_once();
		enqueueEvent(next);
	}
}

bool MuazKurt::Timer::isEmpty()
{
	return eventQueue.empty();
}

void MuazKurt::Timer::age_once()
{
	//if((age_timer - CLOCK::now().time_since_epoch()).count() < 0)
	{
		std::priority_queue<Event> copy;
		//std::cerr << "aging" << age_timer.count() - CLOCK::now().time_since_epoch().count() << std::endl;

		while(!eventQueue.empty())
		{
			Event temp = eventQueue.top();
			eventQueue.pop();
			if(temp._age != MIN_AGE)
				--temp._age;
			std::cerr << temp.name << " " << temp._age << std::endl;
			copy.push(temp);
		}
		eventQueue.swap(copy);
		//age_timer = std::chrono::nanoseconds(CLOCK::now().time_since_epoch().count() + AGE_MILISEC);
	}
}

bool MuazKurt::Timer::alive()
{
	return item_exist;
}


void MuazKurt::Timer::registerTimer(const Timepoint &tp, const TTimerCallback &callback)
{
	enqueueEvent(MuazKurt::Timer::Event("time point", tp, Millisecs::min(), [](){return true;}, callback, MIN_AGE));
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
