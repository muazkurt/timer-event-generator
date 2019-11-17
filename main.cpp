#include "header/Timer.hpp"
#include <iostream>
#include <queue>
int main(void)
{
	auto s = CLOCK::now();
	std::cerr << std::chrono::duration_cast<CLOCK::duration>(Millisecs(2)).count() << std::endl;
	std::cerr << s.time_since_epoch().count() << std::endl;
	std::cerr << (s + Millisecs(2)).time_since_epoch().count() << std::endl;

	std::shared_ptr<MuazKurt::ITimer> x = std::make_shared<MuazKurt::Timer>();
	for(int i = 0; i < 5; ++i)
		x->registerTimer(CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(std::chrono::milliseconds(10000)), [](){std::cerr << "i " << 2 << std::endl;});
	/*for(int i = 0; i < 200; ++i)
	{
		auto adam = CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(std::chrono::milliseconds(10000));
		x->registerTimer([adam](){return CLOCK::now() < adam;}, Millisecs(1000), [i](){std::cerr << "j " << i << std::endl;});
	}
	while(1);*/
}