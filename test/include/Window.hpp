#include "Exstar/Window.h"
class Window : public exstar::Window
{
public:
	exstar::Sprite* sprite = new exstar::Sprite("index.jpg");
	Window(int width,int height,const char* title) : exstar::Window(width,height,title) {
		sprite->resize(exstar::Dimension{800,200});
		setFramerate(60);
	}
	void render(exstar::Camera camera){
		camera.setColor(exstar::Color::Green);
		camera.drawRect(0,0,100,100);
		camera.drawSprite(sprite,100,100);
	}
	void Update(double deltaTime){
		if(isKeyPressed(exstar::Key::D)){
			moveCamera(100*deltaTime,0);
		}else if (isKeyPressed(exstar::Key::A))
		{
			moveCamera(-100*deltaTime,0);
		}
	}
};