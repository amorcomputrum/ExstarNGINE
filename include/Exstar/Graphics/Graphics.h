#pragma once
#include "Exstar/Utils/Point.h"
#include "Exstar/Graphics/Color.h"
#include "Exstar/Graphics/Sprite/Sprite.h"
#include "Exstar/Utils/Vector2d.h"
#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Graphics/Shaders/GLSL.h"
#include "Exstar/Graphics/Shape.h"
namespace exstar{
	class Graphics
	{
	public:
		/**
		 * Initialize the Graphics Object
		 * 
		 * @param width The width of the content to display
		 * @param height The height of the content to display
		 * @param x The x position for the top-left of the Graphics
		 * @param y The y postion for the top-left of the Graphics
		 * 
		 * If Graphics is placed at x=100 and width=100 then contents displayed
		 * will be from x=100 to x = 200
		*/
		Graphics(int width,int height,int x,int y);
		/**
		 * Resize the view of the Graphics
		 * 
		 * @param width The width of the content to display
		 * @param height The height of the content to display
		*/
		void resize(int width,int height);
		/**
		 * Move the Graphics a distance
		 * 
		 * @param x The distance to move the Graphics on the x-axis
		 * @param y The distance to move the Graphics on the y-axis
		*/
		void move(int x,int y);
		/**
		 * Set the Graphics postion
		 * 
		 * @param x The x position to move the Graphics to
		 * @param y The y position to move the Graphics to
		*/
		void set(int x,int y);
		/**
		 * Set the color to use when drawing primitive shapes
		 * 
		 * @param color The Color to use
		*/
		void setColor(exstar::Color color);
		/**
		 * Render a Sprite to the screen
		 * 
		 * @param sprite The sprite to render to the screen
		 * @param x The x position to render the sprite at (top-left)
		 * @param y The y position to render the sprite at (top-left)
		*/
		void drawSprite(exstar::Sprite sprite,int x,int y);
		/**
		 * Render a Sprite to the screen
		 * 
		 * @param sprite The sprite to render to the screen
		 * @param pos The (x,y) postion to render the sprite to (top-left)
		*/
		void drawSprite(exstar::Sprite sprite,exstar::Point pos);
		/**
		 * Render a Rectangle to the screen
		 * 
		 * @param x The x position to render the rectangle at (top-left)
		 * @param y The y position to render the rectangle at (top-left)
		 * @param w The width of the rectangle
		 * @param h The height of the rectangle
		*/
		void drawRect(int x,int y,int w,int h);
		/**
		 * Render a Rectangle to the screen
		 * 
		 * @param pos The postion to render the rectangle to (top-left)
		 * @param size The size of the rectangle to render
		*/
		void drawRect(exstar::Point pos, exstar::Dimension size);
		/**
		 * Render a Rectangle to the screen
		 * 
		 * @param x The x position to render the rectangle at (top-left)
		 * @param y The y position to render the rectangle at (top-left)
		 * @param size The size of the rectangle to render
		*/
		void drawRect(int x,int y, exstar::Dimension size);
		/**
		 * Render a Rectangle to the screen
		 * 
		 * @param pos The postion to render the rectangle to (top-left)
		 * @param w The width of the rectangle
		 * @param h The height of the rectangle
		*/
		void drawRect(exstar::Point pos, int w,int h);
		/**
		 * Render a Ellipse to the screen
		 * 
		 * @param x The x position to render the ellipse at (top-left)
		 * @param y The y position to render the ellipse at (top-left)
		 * @param w The width of the ellipse
		 * @param h The height of the ellipse
		*/
		void drawEllipse(int x,int y,int w,int h);
		/**
		 * Render a Ellipse to the screen
		 * 
		 * @param pos The postion to render the ellipse to (top-left)
		 * @param size The size of the ellipse to render
		*/
		void drawEllipse(exstar::Point pos, exstar::Dimension size);
		/**
		 * Render a Ellipse to the screen
		 * 
		 * @param x The x position to render the ellipse at (top-left)
		 * @param y The y position to render the ellipse at (top-left)
		 * @param size The size of the ellipse to render
		*/
		void drawEllipse(int x,int y, exstar::Dimension size);
		/**
		 * Render a Ellipse to the screen
		 * 
		 * @param pos The postion to render the ellipse to (top-left)
		 * @param w The width of the ellipse
		 * @param h The height of the ellipse
		*/
		void drawEllipse(exstar::Point pos,int w,int h);
		/**
		 * Render a Circle to the screen
		 * 
		 * @param x The x position to render the circle at (top-left)
		 * @param y The y position to render the circle at (top-left)
		 * @param r The radius of the circle to render
		*/
		void drawCircle(int x,int y,int r);
		/**
		 * Render a Circle to the screen
		 * 
		 * @param pos The postion to render the circle to (top-left)
		 * @param r The radius of the circle to render
		*/
		void drawCircle(exstar::Point pos,int r);
		/**
		 * Render a Circle to the screen
		 * 
		 * @param pos The postion to render the circle to (top-left)
		 * @param r The radius of the circle to render
		*/
		void drawCircle(exstar::Vector2d pos,int r);
		
		void drawShape(exstar::Shape shape,int x,int y);

		/**
		 * Render a Pixel
		 * 
		 * @param x The x location of the pixel
		 * @param y The y location of the pixel
		*/
		void drawPixel(int x,int y);
		/**
		 * Render a Pixel
		 * 
		 * @param pos The position of the pixel
		*/
		void drawPixel(exstar::Point pos);
		/**
		 * Render a Pixel
		 * 
		 * @param x The x location of the pixel
		 * @param y The y location of the pixel
		*/
		exstar::Color getPixel(int x,int y);
		/**
		 * Render a Pixel
		 * 
		 * @param pos The position of the pixel
		*/
		exstar::Color getPixel(exstar::Point pos);
		/**
		 * Return the Size of the Graphics
		 * 
		 * @return exstar::Dimension of the size of the Graphics
		*/
		exstar::Dimension getSize();
		/**
		 * Return the Width of the Graphics
		 * 
		 * @return int value of the width of the Graphics
		*/
		int getWidth();
		/**
		 * Return the Height of the Graphics
		 * 
		 * @return int value of the height of the Graphics
		*/
		int getHeight();
		/**
		 * Return the X postion of the Graphics
		 * 
		 * @return int value of the x postion of the Graphics
		*/
		int getX();
		/**
		 * Return the Y postion of the Graphics
		 * 
		 * @return int value of the y postion of the Graphics
		*/
		int getY();


	private:
		/**
		 * The Postion of the Graphics
		*/
		exstar::Point* pos;
		/**
		 * The Size of the Graphics
		*/
		exstar::Dimension* size;
		/**
		 * The Color to use when rendering primative shapes
		*/
		exstar::Color color;
		class Shader{
		public:
			Shader();
			unsigned int* getVAO();
			unsigned int* getVBO();
		private:
			unsigned int VAO,VBO;
		};
		Shader Ellipse;
		Shader Rect;
		Shader Shape;
		Shader Pixel;
		exstar::GLSL spriteShader;
		exstar::GLSL shapeShader;
		void preRender();
		void renderRect();
		void renderEllipse();
		void renderPixel();
		void renderShape();
		void loadSpriteShader();
		void loadShapeShader();
	};
};
