
namespace exstar{
	class Camera
	{
	public:
		Camera(int width,int height,int x,int y);
		void resize(int width,int height);
		void move(int x,int y);
		void set(int x,int y);
		void setColor(exstar::Color color);
		void drawSprite(exstar::Sprite* sprite,int x,int y);
		void drawSprite(exstar::Sprite* sprite,exstar::Point pos);
		void drawRect(int x,int y,int w,int h);
		void drawRect(exstar::Point pos, exstar::Dimension size);
		void drawRect(int x,int y, exstar::Dimension size);
		void drawRect(exstar::Point pos, int w,int h);
		void drawEllipse(int x,int y,int rw,int rh);
		void drawShape();
		exstar::Dimension getSize();
		int getWidth();
		int getHeight();
		int getX();
		int getY();


	private:
		exstar::Point* pos;
		exstar::Dimension* size;
		exstar::Color* color;
	};
}