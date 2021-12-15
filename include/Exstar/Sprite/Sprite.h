#include "Exstar/Utils/Dimension.h"
namespace exstar{
	class Sprite
	{
	public:
		/**
		 * Initialize the Sprite
		 * 
		 * @param file The location of the sprite to load
		*/
		Sprite(const char* file);
		//Sprite(const char* file,int x,int y);
		/**
		 * Destruct the Inialized Sprite
		*/
		~Sprite();
		/**
		 * Change the size of the rendered Sprite when an exstar::Camera renders it
		 * 
		 * @param width The width of the rendered Sprite
		 * @param height The height of the rendered Sprite
		*/
		void resize(int width,int height);
		/**
		 * Change the size of the rendered Sprite when an exstar::Camera renders it
		 * 
		 * @param size The size to render the Sprite
		*/
		void resize(exstar::Dimension size);
		/**
		 * Return the Sprite's native width
		 * 
		 * @return width of the Sprite's native size
		*/
		int getTextureWidth();
		/**
		 * Return the Sprite's native height
		 * 
		 * @return height of the Sprite's native size
		*/
		int getTextureHeight();
		/**
		 * Return the Sprite's native size
		 * 
		 * @return native size of the Sprite
		*/
		exstar::Dimension getTextureSize();
		/**
		 * Return the Sprite's rendered width
		 * 
		 * @return width of the Sprite's rendered size
		*/
		int getWidth();
		/**
		 * Return the Sprite's rendered height
		 * 
		 * @return rendered height of the Sprite
		*/
		int getHeight();
		/**
		 * Return the Sprite's rendered size
		 * 
		 * @return rendered size of the Sprite
		*/
		exstar::Dimension getSize();
		/**
		 * Return the type of the image
		 * 
		 * @return int value of the images type
		 * 3=RGB
		 * 4=RGBA
		*/
		int getType();
		/**
		 * Return the Image data
		 * 
		 * @return The Image data of the Sprite
		*/
		unsigned char * getImage();
	private:
		/**
		 * The location of the image in the Image_Handler.h
		*/
		int fileIndex;
		/**
		 * The type for the image
		 * 3=RGB
		 * 4=RGBA
		*/
		int type;
		/**
		 * The location of the sprite to load
		*/
		const char* file;
		/**
		 * The native size of the Sprite
		*/
		exstar::Dimension textureSize;
		/**
		 * The rendered size of the Sprite
		*/
		exstar::Dimension size;

	};
}