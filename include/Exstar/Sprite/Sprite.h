namespace exstar{
	class Sprite
	{
	public:
		Sprite(const char* file,int w,int h);
		Sprite(const char* file,int x,int y,int w,int h);
		~Sprite();
		int getX();
		int getY();
		exstar::Point getPoint();
		int getWidth();
		int getHeight();
		exstar::Dimension getSize();
		unsigned char * getImage();
	private:
		int fileIndex;
		const char* file;
		exstar::Point pos;
		exstar::Dimension size;

	};
}