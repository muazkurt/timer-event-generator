#include "header/Timer.hpp"
#include <iostream>
#include <queue>
int main(void)
{
	std::unique_ptr<MuazKurt::ITimer> x = std::make_unique<MuazKurt::Timer>();
	/*for(int i = 0; i < 40; ++i)
	{
		x->registerTimer(CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(Millisecs(i * 7)), 
						[](){
							//std::cout << "im a one time operation: " << i << "with " << i * 7 << "time period." << std::endl;
							});
	}
	for(int i = 1; i < 200; ++i)
	{*/
		x->registerTimer(
			Millisecs(1000), 
			[]()
			{
				std::cout << "Im the periodic event: 1. My period is " << Millisecs(1000).count() << std::endl;
			}
		);
		x->registerTimer(
			Millisecs(500), 
			[]()
			{
				std::cout << "Im the periodic event: 2. My period is " << Millisecs(50).count() << std::endl;
			}
		);
	//}
	for(int i = 0; i < INT32_MAX % 10000000000; ++i);
	//getc(stdin);
	return 0;
}