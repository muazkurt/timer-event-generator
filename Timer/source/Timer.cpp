#include <Timer.hpp>

bool MuazKurt::Timer::item_exist = false;

int	MuazKurt::Timer::item_number = 0;

MuazKurt::Timer::Timer() : queueSaver(), eventQueue(), logger(std::to_string(CLOCK::now().time_since_epoch().count()))
{
	item_exist = true;
	timer.init(MuazKurt::theJob, this);
}
MuazKurt::Timer::~Timer()
{
	item_exist = false;
}

void MuazKurt::Timer::enqueueEvent(const Timepoint & tp,
									const Millisecs & ms,
									const TPredicate & pd,
									const TTimerCallback & cb)
{
	std::unique_lock<std::mutex> lg(queueSaver);
	++item_number;
	eventQueue.push(MuazKurt::Timer::Event(tp, ms, pd, cb));
	condition.notify_one();
}

void MuazKurt::Timer::enqueueEvent(const MuazKurt::Timer::Event & enquable)
{
	std::unique_lock<std::mutex> lg(queueSaver);
	eventQueue.push(enquable);
	condition.notify_one();
}

void MuazKurt::Timer::one_job() 
{
	MuazKurt::Timer::Event	next;
	bool					possible = false;
	{
		std::unique_lock<std::mutex> lg(queueSaver);
		next = eventQueue.top();
		if((possible = (std::chrono::duration_cast<CLOCK::duration>(next.next_work - CLOCK::now()).count() < 
						std::chrono::duration_cast<CLOCK::duration>(Millisecs(5)).count())))
			eventQueue.pop();
	}
	if(possible && next.doit())
	{
		if(abs(std::chrono::duration_cast<Millisecs>(next.next_work - CLOCK::now()).count()) > 5)
			logger << "Job " << next.name << " deadline error.\n"; 
		next.next_work = next.period + CLOCK::now();
		enqueueEvent(next);
	}
}

bool MuazKurt::Timer::isEmpty()
{
	std::unique_lock<std::mutex> lg(queueSaver);
	if(eventQueue.empty())
		condition.wait_for(lg, std::chrono::microseconds(200));
	return eventQueue.empty();
}

bool MuazKurt::Timer::alive()
{
	return item_exist;
}

void MuazKurt::Timer::registerTimer(const Timepoint &tp, const TTimerCallback &callback)
{
	enqueueEvent(tp, Millisecs::min(), [](){return true;}, callback);
}

void MuazKurt::Timer::registerTimer(const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(CLOCK::now(), period, [](){return true;}, callback);
}

void MuazKurt::Timer::registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(CLOCK::now(), period,
		[tp](){return ((tp - CLOCK::now()).count() > 0);}, callback);
}

void MuazKurt::Timer::registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &callback)
{
	enqueueEvent(CLOCK::now(), period, pred, callback);
}
