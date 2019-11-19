#include "header/Timer.hpp"
#include <iostream>
#include <queue>
int main(void)
{
	std::unique_ptr<MuazKurt::ITimer> x = std::make_unique<MuazKurt::Timer>();
	for(int i = 0; i < 40; ++i)
		x->registerTimer(CLOCK::now() + std::chrono::duration_cast<CLOCK::duration>(Millisecs(i * 7)), 
						[i](){
							std::cout << "im a one time operation: " << i << ". I will be done after " << Millisecs(i * 7).count() << " milisecs." << std::endl;
							});
	for(int i = 1; i < 200; ++i)
		x->registerTimer(
			Millisecs(i * 5), 
			[i]()
			{
				std::cout << "Im the periodic event: " << i << ". My period is " << Millisecs(i * 5).count() << std::endl;
			}
		);
	for(int i = 0; i < 22222; ++i);
	return 0;
}