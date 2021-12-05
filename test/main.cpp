#include <Window.hpp>

int main()
{
	Window* window = new Window(800,200,"Test Window");
	window->setIcon("testIcon.png");
	window->run();
	return 0;
}
