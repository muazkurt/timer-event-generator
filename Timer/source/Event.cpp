#include <Timer.hpp>

MuazKurt::Timer::Event::Event(const Timepoint & tp, const Millisecs & ms, const TPredicate & pd, const TTimerCallback & cb) : 
	name(MuazKurt::Timer::item_number), next_work(tp), period(ms), predicate(pd), callback(cb)
{/*-,-*/}


MuazKurt::Timer::Event::Event(const MuazKurt::Timer::Event & other) : 
	name(other.name), 
	next_work(other.next_work), 
	period(other.period), 
	predicate(other.predicate), 
	callback(other.callback)
{/*-,-*/}


MuazKurt::Timer::Event::~Event()
{/*-,-*/}


bool MuazKurt::operator <(const MuazKurt::Timer::Event & a, const MuazKurt::Timer::Event & b)
{
	return a.next_work > b.next_work;
}

const MuazKurt::Timer::Event & MuazKurt::Timer::Event::operator =(const  MuazKurt::Timer::Event & other)
{
	this->callback	= other.callback;
	this->name		= other.name;
	this->next_work	= other.next_work;
	this->period	= other.period;
	this->predicate	= other.predicate;
	return *this;
}

bool MuazKurt::Timer::Event::doit()
{
	bool _periodic = (period != Millisecs::min());
	if(predicate())
		callback();
	else _periodic = false;
	return _periodic;
}

void MuazKurt::theJob(MuazKurt::Timer * const timerObject)
{
	while(MuazKurt::Timer::alive())
	{
		/** Condition Variable **/
		if(!timerObject->isEmpty())
			timerObject->one_job();
	}
}