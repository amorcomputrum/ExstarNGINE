#include <Window.hpp>

int main()
{
	Window* window = new Window(800,200,"Test Window");
	window->setBackgroundColor(exstar::Color(255,0,0));
	window->setIcon("testIcon.png");
	window->run();
	return 0;
}
