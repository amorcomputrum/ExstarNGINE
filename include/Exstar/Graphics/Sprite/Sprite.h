#pragma once

#include "Exstar/Graphics/Shaders/GLSL.h"
#include "Exstar/System/CompressedAsset.h"
#include "Exstar/Utils/Dimension.h"
#include "Exstar/Utils/Point.h"

namespace exstar{
	class Sprite
	{
	public:
		Sprite();
		/**
		 * Initialize the Sprite
		 * 
		 * @param FILE The location of the sprite to load
		*/
		Sprite(std::string FILE);
		/**
		 * Initialize the Sprite
		 * 
		 * @param FILE The location of the sprite to load
		 * @param x The x location of the sprite to render(This is for rendering only part of a sprite from the file)
		 * @param y The y location of the sprite to render(This is for rendering only part of a sprite from the file)
		 * @param w The width of the area to render from the FILE
		 * @param h The height of the area to render from the FILE
		*/
		Sprite(std::string FILE, int x, int y, int w, int h);
		/**
		 * Initialize the Sprite
		 * 
		 * @param FILE the file to load sprite
		*/
		Sprite(exstar::CompressedAsset FILE);
		/**
		 * Initialize the Sprite
		 * 
		 * @param FILE the file to load sprite
		 * @param x The x location of the sprite to render(This is for rendering only part of a sprite from the file)
		 * @param y The y location of the sprite to render(This is for rendering only part of a sprite from the file)
		 * @param w The width of the area to render from the FILE
		 * @param h The height of the area to render from the FILE
		*/
		Sprite(exstar::CompressedAsset FILE, int x, int y, int w, int h);
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
		void resize(int width, int height);
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
		 * The rendered size of the Sprite
		*/
		exstar::Dimension size;

		unsigned int texture,VAO,VBO,EBO;
		void loadShader(int x,int y,int width, int height,int imageW, int imageH,int type,unsigned char* data);

	};
};
