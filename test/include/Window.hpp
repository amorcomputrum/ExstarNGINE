#include <Exstar/Window.h>

class Window : public exstar::Window
{
public:
	exstar::Sprite* sprite = new exstar::Sprite("testIcon.png",64,64);
	Window(int width,int height,const char* title) : exstar::Window(width,height,title){
	}
	void render(exstar::Camera camera){
		camera.drawSprite(sprite,0,0);
	}
	
};