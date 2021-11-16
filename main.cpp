#include <Exstar/Window.h>


int main()
{
	exstar::Window* window = new exstar::Window(800,200,"Test Window");
	window->setIcon("testIcon.png");
	window->run();
	return 0;
}
