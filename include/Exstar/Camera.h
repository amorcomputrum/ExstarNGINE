
#ifndef Camera_H
#define Camera_H
	#include "Exstar/Utils/Point.h"
	#include "Exstar/Utils/Color.h"
	#include "Exstar/Sprite/Sprite.h"
	#include "Exstar/Utils/ArrayList.h"
	namespace exstar{
		class Camera
		{
		public:
			/**
			 * Initialize the Camera Object
			 * 
			 * @param width The width of the content to display
			 * @param height The height of the content to display
			 * @param x The x position for the top-left of the camera
			 * @param y The y postion for the top-left of the camera
			 * 
			 * If camera is placed at x=100 and width=100 then contents displayed
			 * will be from x=100 to x = 200
			*/
			Camera(int width,int height,int x,int y);
			/**
			 * Resize the view of the Camera
			 * 
			 * @param width The width of the content to display
			 * @param height The height of the content to display
			*/
			void resize(int width,int height);
			/**
			 * Move the camera a distance
			 * 
			 * @param x The distance to move the camera on the x-axis
			 * @param y The distance to move the camera on the y-axis
			*/
			void move(int x,int y);
			/**
			 * Set the camera postion
			 * 
			 * @param x The x position to move the camera to
			 * @param y The y position to move the camera to
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
			void drawSprite(exstar::Sprite* sprite,int x,int y);
			/**
			 * Render a Sprite to the screen
			 * 
			 * @param sprite The sprite to render to the screen
			 * @param pos The (x,y) postion to render the sprite to (top-left)
			*/
			void drawSprite(exstar::Sprite* sprite,exstar::Point pos);
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
			 * Render a Custom Shape
			 * 
			 * @param shape The Verticies to render onto the defined canvas
			 * @param x The left x location of the canvas to draw on
			 * @param y The top y location of the canvas to draw on
			 * @param w The width of the canvas to draw on
			 * @param h The height of the canvas to draw on
			*/
			void drawShape(exstar::ArrayList<exstar::Point>* shape,int x,int y,int w,int h);
			/**
			 * Render a Custom Shape
			 * 
			 * @param shape The Verticies to render onto the defined canvas
			 * @param pos The top-left location of the canvas
			 * @param w The width of the canvas to draw on
			 * @param h The height of the canvas to draw on
			*/
			void drawShape(exstar::ArrayList<exstar::Point>* shape,exstar::Point pos,int w,int h);
			/**
			 * Render a Custom Shape
			 * 
			 * @param shape The Verticies to render onto the defined canvas
			 * @param pos The top-left location of the canvas
			 * @param size The size of the canvas to draw on
			*/
			void drawShape(exstar::ArrayList<exstar::Point>* shape,exstar::Point pos,exstar::Dimension size);
			/**
			 * Render a Custom Shape
			 * 
			 * @param shape The Verticies to render onto the defined canvas
			 * @param x The left x location of the canvas to draw on
			 * @param y The top y location of the canvas to draw on
			 * @param size The size of the canvas to draw on
			*/
			void drawShape(exstar::ArrayList<exstar::Point>* shape,int x,int y,exstar::Dimension size);
			/**
			 * Return the Size of the camera
			 * 
			 * @return exstar::Dimension of the size of the Camera
			*/
			exstar::Dimension getSize();
			/**
			 * Return the Width of the camera
			 * 
			 * @return int value of the width of the camera
			*/
			int getWidth();
			/**
			 * Return the Height of the camera
			 * 
			 * @return int value of the height of the camera
			*/
			int getHeight();
			/**
			 * Return the X postion of the camera
			 * 
			 * @return int value of the x postion of the camera
			*/
			int getX();
			/**
			 * Return the Y postion of the camera
			 * 
			 * @return int value of the y postion of the camera
			*/
			int getY();


		private:
			/**
			 * The Postion of the Camera
			*/
			exstar::Point* pos;
			/**
			 * The Size of the Camera
			*/
			exstar::Dimension* size;
			/**
			 * The Color to use when rendering primative shapes
			*/
			exstar::Color* color;
		};
	};
	#include "Exstar/Camera.cpp"
#endif