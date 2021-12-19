#include "Exstar/Clock.h"

exstar::Clock::Clock(){
	start();
}
void exstar::Clock::start(){
	time = std::chrono::high_resolution_clock::now();
}
double exstar::Clock::getTime(){
	return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - time).count();
}