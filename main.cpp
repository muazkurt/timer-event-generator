#include <Timer.hpp>
int main(void)
{
	std::unique_ptr<MuazKurt::ITimer> x = std::make_unique<MuazKurt::Timer>();
	for(int i = 2; i < 2000; ++i)
		x->registerTimer(
			CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(Millisecs(i * 10)), 
			[](){return;});
	for(int i = 1; i < 2000; ++i)
		x->registerTimer(
			Millisecs(i * 10), 
			[](){return;});
	for(int i = 1; i < 2000; ++i)
		x->registerTimer(
			CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(Millisecs(i * 10)),
			Millisecs(i * 10), 
			[](){return;});
	for(int i = 2; i < 2000; ++i)
	{
		auto timep = CLOCK::now();
		x->registerTimer(
			[timep](){return (timep - CLOCK::now()).count() > std::chrono::seconds(120).count();},
			Millisecs(i * 10), 
			[](){return;});
	}
	std::this_thread::sleep_for(std::chrono::seconds(120));
	return 0;
}