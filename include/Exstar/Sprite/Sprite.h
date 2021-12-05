namespace exstar{
	class Sprite
	{
	public:
		Sprite(const char* file,int w,int h);
		Sprite(const char* file,int x,int y);
		~Sprite();
		int getX();
		int getY();
		Point getPoint();
		int getWidth();
		int getHeight();
		Dimension getSize();
		unsigned char * getImage();
	private:
		int fileIndex;
		std::string file;
		Point pos;
		Dimension size;

	};
}