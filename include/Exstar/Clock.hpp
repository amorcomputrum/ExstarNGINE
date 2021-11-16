#include <time.h>
namespace exstar{
	class Clock
	{
	public:
		Clock(){
			start();
		}
		void start(){
			time = std::chrono::high_resolution_clock::now();
		}
		double getTime(){
			return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-time).count();
		}
	private:
		std::chrono::_V2::system_clock::time_point time;
		
	};
}