#include "Exstar/Window.h"
class Window : public exstar::Window
{
public:
	exstar::Sprite* sprite = new exstar::Sprite("testIcon.png");
	exstar::Sprite* sprite1 = new exstar::Sprite("index.jpg");
	Window(int width,int height,const char* title) : exstar::Window(width,height,title) {
		sprite1->resize(exstar::Dimension{100,100});
		exstar::Vector2d distance(10,0);
		moveCamera(distance);
	}
	void render(exstar::Camera camera){
		camera.drawSprite(sprite1,10,0);
		
	}
};