namespace exstar{
	class Sprite
	{
	public:
		Sprite(const char* file);
		Sprite(const char* file,int x,int y);
		~Sprite();
		void resize(int width,int height);
		int getTextureWidth();
		int getTextureHeight();
		int getWidth();
		int getHeight();
		int getType();
		exstar::Dimension getSize();
		unsigned char * getImage();
	private:
		int fileIndex;
		int type;
		const char* file;
		exstar::Dimension textureSize;
		exstar::Dimension size;

	};
}