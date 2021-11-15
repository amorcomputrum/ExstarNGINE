#include <Exstar/Window.hpp>


int main()
{
	exstar::Window* window = new exstar::Window(800,200,"Fuck You");
	window->setIcon("testIcon.png");
	window->run();
	return 0;
}