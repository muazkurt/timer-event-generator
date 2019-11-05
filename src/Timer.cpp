#include "Timer.hpp"

Timer::Timer()
{}

Timer::Timer(const Timer::Timer & other)
{}

const Timer::Timer & Timer::operator=(const Timer::Timer & other)
{}

Timer::~Timer()
{}

void Timer::registerTimer(const Timepoint &tp, const TTimerCallback &cb)
{}

void Timer::registerTimer(const Millisecs & period, const TTimerCallback &cb)
{}

void Timer::registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb)
{}

void Timer::registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb)
{}