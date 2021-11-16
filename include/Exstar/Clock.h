#include <time.h>
namespace exstar{
	class Clock
	{
	public:
		Clock();
		void start();
		double getTime();
	private:
		std::chrono::_V2::system_clock::time_point time;
		
	};
}