#include "Exstar/Window.h"
class Window : public exstar::Window
{
public:
	exstar::Sprite* sprite = new exstar::Sprite("testIcon.png");
	exstar::Sprite* sprite1 = new exstar::Sprite("index.jpg");
	Window(int width,int height,const char* title) : exstar::Window(width,height,title) {
		sprite1->resize(100,100);
		moveCamera(10,0);
	}
	void render(exstar::Camera camera){
		camera.drawSprite(sprite1,10,0);
		
	}
};