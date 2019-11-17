#include "../header/Timer.hpp"

MuazKurt::Timer::Event::Event(const String & n, const Timepoint & tp, const Millisecs & ms, const TPredicate & pd, const TTimerCallback & cb, int age) : 
	name("" + n), next_work(tp), period(ms), predicate(pd), callback(cb), _age(age)
{/*_._*/}


MuazKurt::Timer::Event::Event(const MuazKurt::Timer::Event & other) : 
	MuazKurt::Timer::Event::Event(other.name, other.next_work, other.period, other.predicate, other.callback, other._age)
{/*_._*/}


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
	this->_age		= other._age;
	return *this;
}

bool MuazKurt::Timer::Event::doit()
{
	bool _periodic = (period != Millisecs::min());
	if(predicate())
	{
		//++_age;
		callback();
	}
	else _periodic = false;
	return _periodic;
}

void MuazKurt::theJob(MuazKurt::Timer * const timerObject)
{
	while(MuazKurt::Timer::alive())
	{
		if(!timerObject->isEmpty())
			timerObject->one_job();
	}
}