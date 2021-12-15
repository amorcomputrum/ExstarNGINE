#include <chrono>
#include <time.h>
namespace exstar{
	class Clock
	{
	public:
		Clock();
		/**
		 * Gets the current time and stores it for later calculations
		 * time-startTime = ellapsed time
		*/
		void start();
		/**
		 * Calculates the ellapsed time
		 * 
		 * @return ellapsed time in milliseconds
		*/
		double getTime();
	private:
		std::chrono::_V2::system_clock::time_point time;
		
	};
}