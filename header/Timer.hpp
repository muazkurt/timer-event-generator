#ifndef TIMER_H
	#define TIMER_H
	#include "ITimer.hpp"
	#include <thread>
	class Timer : public ITimer
	{
		public:
			Timer();
			Timer(const Timer & other);
			const Timer & operator=(const Timer & other);
			~Timer();
			virtual void registerTimer(const Timepoint &tp, const TTimerCallback &cb);
			virtual void registerTimer(const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);
		private:
			std::thread timer;

			struct Event
			{
				Timepoint		tp;
				Millisecs		ms;
				TPredicate 		pr;
				TTimerCallback	cb;
				void doit()
				{
					if(pr._M_empty)
						cb();
				}
			};
			
	};
#endif
