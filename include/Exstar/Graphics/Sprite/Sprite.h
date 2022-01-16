#pragma once
#include "Exstar/Utils/Dimension.h"
#include "Exstar/Utils/Point.h"
#include "Exstar/Graphics/Shaders/GLSL.h"
namespace exstar{
	class Sprite
	{
	public:
		Sprite();
		/**
		 * Initialize the Sprite
		 * 
		 * @param file The location of the sprite to load
		*/
		Sprite(const char* file);
		/**
		 * Initialize the Sprite
		 * 
		 * @param file The location of the sprite to load
		 * @param x The x location of the sprite to render(This is for rendering only part of a sprite from the file)
		 * @param y The y location of the sprite to render(This is for rendering only part of a sprite from the file)
		 * @param w The width of the area to render from the file
		 * @param h The height of the area to render from the file
		*/
		Sprite(const char* file,int x,int y,int w,int h);
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
		unsigned int getVAO();
		void Bind();
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
		 * The edited size of the Sprite
		 * When only loading part of the sprite
		*/
		exstar::Dimension cutSize;
		/**
		 * The rendered size of the Sprite
		*/
		exstar::Dimension size;
		/**
		 * The x,y on the Sprite
		*/
		exstar::Point Pos;
		unsigned int texture,VAO,VBO,EBO;
		void loadShader();

	};
};
