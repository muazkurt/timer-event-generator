#ifndef TIMER_H
	#define TIMER_H
	#include "ITimer.hpp"
	#include "Guard.hpp"
	#include <queue>
	namespace MuazKurt
	{
		class Timer : public ITimer
		{
		public:
			Timer();
			virtual void registerTimer(const Timepoint &tp, const TTimerCallback &cb);
			virtual void registerTimer(const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);
			class Event
			{
			private:
				String			name;
				Timepoint		next_work;
				Millisecs		period;
				TPredicate 		predicate;
				TTimerCallback	callback;
			public:
				Event(const String & n, const Timepoint & tp, const Millisecs & ms, const TPredicate & pd, const TTimerCallback & cb) : 
					name(n), next_work(tp), period(ms), predicate(pd), callback(cb)
				{/*_._*/}
				Event(const Event & other) : Event(other.name, other.next_work, other.period, other.predicate, other.callback)
				{/*_._*/}
				bool doit();
				bool operator <(const Timer::Event& a);
				inline const String	&			get_name() 		const {return name;}
				inline const Timepoint &		get_next_work() const {return next_work;}
				inline const Millisecs &		get_period() 	const {return period;}
			};
			const Event & peek();
			const void dequeue();
			void enqueueEvent(const struct Event & enqueable);
			bool isEmpty();
		private:
			ThreadGuard timer;
			std::mutex queueSaver;
			std::priority_queue<Event> eventQueue;
		};
		bool operator <(const Timer::Event& a, const Timer::Event& b);

		void theJob(Timer * timerObject);
	} // namespace MuazKurt
#endif
