#include "Exstar/Window.h"
class Window : public exstar::Window
{
public:
	Window(int width,int height,const char* title) : exstar::Window(width,height,title) {
		setFramerate(60);
	}
	void render(exstar::Camera camera){
		camera.setColor(exstar::Color::Black);
		camera.drawRect(0,0,50,100);
		camera.setColor(exstar::Color::Blue);
		camera.drawEllipse(0,0,50,100);
	}

};