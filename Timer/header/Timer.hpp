#ifndef TIMER_H
	#define TIMER_H
	#include "ITimer.hpp"
	#include "FileGuard.hpp"
	#include "ThreadGuard.hpp"
	#include <queue>
	#include <condition_variable> 
	namespace MuazKurt
	{
		/**
		 * This is a class to imlement ITimer interface
		 * for generating periodic events with given time intervals or predicates.
		 * This class generates a thread by itself.
		 **/
		class Timer : public ITimer
		{
		public:
			/**
			 * Creates the object, initilizes thread_guard, condition variable,
			 * mutex and file_guard to work. Sets the alive flag.
			 **/
			Timer();

			/**
			 * Clears all its held objects, open files etc. Clears alive flag.
			 **/
			~Timer();
			
			/**
			 * Overloading functions.
			 **/
			virtual void registerTimer(const Timepoint &tp, const TTimerCallback &cb);
			virtual void registerTimer(const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
			virtual void registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);

			/**
			 * Public callable function to generate one event. 
			 * Checks an event's next work period and generates the event.
			 * If it is an periodic event, enqueues the event again for the next call.
			 **/
			void one_job();
			/**
			 * Checks for the emptyness of the queue.
			 **/
			bool isEmpty();
			/**
			 * Static checker for the object aliveness.
			 * If the object had destructed, then it will be false.
			 **/
			static bool alive();

			/**
			 * A struct that assambles all the necessary information about an event.
			 * Each of the Event items has their own names. This way each one of them will 
			 * be seperated from each other.
			 **/
			struct Event
			{
				// Id of the Event
				int				name;
				// The next working time point to schedule.
				Timepoint		next_work;
				// Period of the event.
				Millisecs		period;
				// A predicate that must be satisfied before calling the callback.
				TPredicate 		predicate;
				// The actual callback of the object.
				TTimerCallback	callback;
				Event(const Timepoint & tp = CLOCK::now(), 
					const Millisecs & ms = Millisecs::min(), 
					const TPredicate & pd = nullptr, 
					const TTimerCallback & cb = nullptr);
				Event(Event & other);
				Event(const Event & other);
				~Event();
				const Event & operator = (const Event & other);
				/**
				 * Generates the event. It checks the predicate for doing the job, 
				 * period for adding the job to the queue again. If both have satisfied, 
				 * then returns true.
				 **/
				bool doit();
			};
		private:
			// A thread guard for running/terminating the thread clearly.
			ThreadGuard					timer;
			// The mutex for saving the queue for updates.
			std::mutex					queueSaver;
			// Priority queue to schedule events based on their work times.
			std::priority_queue<Event>	eventQueue;
			// Condition for waiting for adding a new event into the priority queue.
			std::condition_variable		condition;
			// True if the class instance is currently available.
			static bool 				item_exist;
			// Event numbers.
			static int					item_number;
			// Logger file guard. Opened with constructer, deleted with destructer.
			FileGuard					logger;
			// Enqueue one event to the queue by increasing item_number.
			void enqueueEvent(	const Timepoint & tp, 
								const Millisecs & ms, 
								const TPredicate & pd, 
								const TTimerCallback & cb);
			// Enqueue one event that have been enqueued.
			void enqueueEvent(const MuazKurt::Timer::Event &);
		};
		/**
		 * This method is must be implemented because the priority_queue class says so.
		 * If sbd. uses this class with its own type, then he/she must implement this method on it also.
		 * This method compares two Event instances wrt. their next working time.
		 * If a's next work is closer than b', returns true.
		 **/
		bool operator <(const Timer::Event & a, const Timer::Event & b);
		/**
		 * Stay alive if the timerObject is alive,
		 * If the object is dead, finishes its job.
		 * Otherwise, checks if it contains an event to generate, generates it.
		 **/
		void theJob(Timer * const timerObject);
	} // namespace MuazKurt
#endif
