#ifndef TIMER_H
	#define TIMER_H
	#define AGE_MILISEC	10000
	#define MAX_AGE 	255
	#define MIN_AGE 	1
	#include "ITimer.hpp"
	#include "Guard.hpp"
	#include <queue>
	namespace MuazKurt
	{
		class Timer : public ITimer
		{
		public:
			Timer();
			~Timer();
			/**
			 * Overloading functions.
			 **/
			virtual void registerTimer(const Timepoint &tp, const TTimerCallback &cb);
			virtual void registerTimer(const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);
			struct Event
			{
				String			name;
				int 			_age;
				Timepoint		next_work;
				Millisecs		period;
				TPredicate 		predicate;
				TTimerCallback	callback;
				Event(const String & n = "",
					const Timepoint & tp = CLOCK::now(), 
					const Millisecs & ms = Millisecs::min(), 
					const TPredicate & pd = nullptr, 
					const TTimerCallback & cb = nullptr,
					int age = MAX_AGE);
				Event(Event & other);
				Event(const Event & other);
				const Event & operator = (const Event & other);
				bool doit();
			};
			void one_job();
			bool isEmpty();
			static bool alive();
		private:
			ThreadGuard timer;
			std::mutex queueSaver;
			std::priority_queue<Event>	eventQueue;
			std::chrono::nanoseconds	age_timer;
			static bool item_exist;
			void age_once();
			void enqueueEvent(const MuazKurt::Timer::Event &);
		};
		bool operator <(const Timer::Event & a, const Timer::Event & b);

		void theJob(Timer * const timerObject);
	} // namespace MuazKurt
#endif
