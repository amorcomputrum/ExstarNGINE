namespace exstar{
	class Sprite
	{
	public:
		Sprite(const char* file);
		Sprite(const char* file,int x,int y);
		~Sprite();
		void resize(int width,int height);
		void resize(exstar::Dimension change);
		int getTextureWidth();
		int getTextureHeight();
		exstar::Dimension getTextureSize();
		int getWidth();
		int getHeight();
		exstar::Dimension getSize();
		int getType();
		unsigned char * getImage();
	private:
		int fileIndex;
		int type;
		const char* file;
		exstar::Dimension textureSize;
		exstar::Dimension size;

	};
}