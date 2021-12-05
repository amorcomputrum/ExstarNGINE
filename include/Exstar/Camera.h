#include "Sprite.h"
namespace exstar{
	class Camera
	{
	public:
		Camera(int width,int height,int x,int y);
		void resize(int width,int height);
		void move(int x,int y);
		void set(int x,int y);
		void drawSprite();
		void drawRect(int x,int y,int w,int h);
		void drawEllipse(int x,int y,int rw,int rh);
		void drawShape();
		exstar::Dimension getSize();
		int getWidth();
		int getHeight();
		int getX();
		int getY();


	private:
		int width,height,x,y;
	};
}