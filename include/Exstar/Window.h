#pragma once

#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION

//include Dependencies
#include "GLFW/glfw3.h"


#include <iostream>
#include <chrono>
#if defined(__WIN32) || defined(_WIN64)
	#include <Windows.h>
#else
	#include <unistd.h>
#endif


#include "Exstar/Graphics/Graphics.h"
#include "Exstar/Utils/Vector2d.h"
#include "Exstar/Clock.h"
#include "Exstar/Key.h"
#include "Exstar/MouseEvent.h"

namespace exstar{
	class Window {
	public:
		/**
		 * Initialize The Window Object
		 * 
		 * @param width The width of the window to display
		 * @param height The height of the window to display
		 * @param title The title of the window to display
		*/
		Window(int width, int height, std::string title);
		//-------------Virtual Functions-------------
		/**
		 * Function that renders to display
		 * 
		 * @param Graphics The Graphics that is used to render to the window 
		*/
		virtual void render(Graphics g);
		/**
		 * Function that Updates every frame
		 * 
		 * @param deltaTime The elapsed time
		*/
		virtual void Update(double deltaTime);
		/**
		 * Event called on window resize
		 * 
		 * @param size The new size of the display
		*/
		virtual void onResize(exstar::Dimension size);
		/**
		 * Event called on key press
		 * 
		 * @param key Key that was pressed
		*/
		virtual void keyPressed(int key);
		/**
		 * Event called on key release
		 * 
		 * @param key Key that was released
		*/
		virtual void keyReleased(int key);
		/**
		 * Event called on mouse press
		 * 
		 * @param event The location and button that was pressed
		*/
		virtual void mousePressed(MouseEvent* event);
		/**
		 * Event called on mouse release
		 * 
		 * @param event The location and button that was released
		*/
		virtual void mouseReleased(MouseEvent* event);
		//-------------Public Functions-------------
		/**
		 * Begins the main loop and displays window
		*/ 
		void run();
		/**
		 * closes the window and stops the program
		*/ 
		void close();

		void setBufferCount(int count);


		/**
		 * Sets the framerate of the program
		 * 
		 * @param frameRate The framerate to set the program to
		*/ 
		void setFramerate(int frameRate);
		/**
		 * Sets the Icon of the window
		 * 
		 * @param path The location of the image to load as icon
		*/ 
		void setIcon(const char* path);
		/**
		 * Sets the Title of the window
		*/
		void setTitle(std::string title);
		/**
		 * Set the size limits of the window
		 * 
		 * @param minW The minimum width the window can have
		 * @param minH The minimum height the window can have
		 * @param maxW The maximum width the window can have
		 * @param maxHThe maximum height the window can have 
		*/
		void setSizeLimits(int minW, int minH, int maxW, int maxH);
		/**
		 * Set the size of the window
		 * 
		 * @param width The width to set the window to
		 * @param height The height to set the window to
		*/
		void setSize(int width, int height);
		/**
		 * Set the size of the window
		 * 
		 * @param size The Dimensions to set the window to
		*/
		void setSize(exstar::Dimension size);
		/** 
		 * Sets whether or not the Camera will move on the resize event
		 * 
		 * @param state Boolean for whether the Camera will move
		*/
		void setAdjustCameraOnResize(bool state);
		/**
		 * Sets the Background Color of the window
		 * 
		 * @param r Red Color 0-255
		 * @param g Green Color 0-255
		 * @param b Black Color 0-255
		*/
		void setBackgroundColor(double r, double g, double b);
		/**
		 * Sets the Background Color of the window
		 * 
		 * @param r Red Color 0-255
		 * @param g Green Color 0-255
		 * @param b Black Color 0-255
		 * @param a Alpha Color 0-255
		*/
		void setBackgroundColor(double r, double g, double b, double a);
		/**
		 * Sets the Background Color of the window
		 * 
		 * @param color Color to set the background to
		*/
		void setBackgroundColor(exstar::Color color);
		/**
		 * Moves the Camera
		 * 
		 * @param x The distance to move on the x-axis
		 * @param y The distance to move on the y-axis
		*/
		void moveCamera(int x, int y);
		/**
		 * Moves the Camera
		 * 
		 * @param distance 2D-Vector for change on x and y axis
		*/
		void moveCamera(exstar::Vector2d distance);
		/**
		 * Sets the Position of the Camera
		 * 
		 * @param x The x position to set the Camera to
		 * @param y The y position to set the Camera to
		*/
		void setCamera(int x, int y);
		/**
		 * Sets the Position of the Camera
		 * 
		 * @param pos The postion to set the Camera to
		*/
		void setCamera(exstar::Point pos);
		/**
		 * Returns the Title of the window
		 * 
		 * @return title of the window
		*/
		std::string getTitle();
		/**
		 * Return whether a key is pressed
		 * 
		 * @param key The key to check
		 * @return if key is pressed
		*/
		bool isKeyPressed(int key);
		/**
		 * Returns the size of the window
		 * 
		 * @return Dimension of the window
		*/
		exstar::Dimension getSize();
		/**
		 * Returns the Mouse's Position
		 * 
		 * @return Point of the mouse postion
		*/
		exstar::Point getMousePos();
		/**
		 * Returns DeltaTime
		 * 
		 * @return the current deltaTime
		*/
		double DeltaTime();
		/**
		 * Returns the X position of the mouse
		 * 
		 * @return the x-axis position of the mouse
		*/
		int getMouseX();
		/**
		 * Returns the Y position of the mouse
		 * 
		 * @return the y-axis position of the mouse
		*/
		int getMouseY();
		/**
		 * Returns the Width of the window
		 * 
		 * @return the width of the window
		*/
		int getWidth();
		/**
		 * Returns the Height of the window
		 * 
		 * @return the height of the window
		*/
		int getHeight();
		/**
		 * Returns whether the Camera is allowed to move on resize
		 * 
		 * @return state of adjustGraphicsOnResize
		*/
		bool getAdjustCameraOnResize();

	protected:
		/**
		 * The Graphics for the window
		*/
		exstar::Graphics* g;

	private:
		/**
		 * ArrayList of the Keys that are currently pressed
		*/
		static exstar::ArrayList<int>* keysPressed;
		/**
		 * ArrayList of the Mouse buttons that are currently pressed
		*/
		static exstar::ArrayList<exstar::MouseEvent*>* mouseEvents;
		/**
		 * Seprate copy of the keysPressed
		 * used to determine when to call a key event such as keyReleased()
		*/
		exstar::ArrayList<int>* keysPressedCopy = new exstar::ArrayList<int>();
		/**
		 * Copy of mouseEvents
		 * used to determine when to call mouse event such as mousePressed()
		*/
		exstar::ArrayList<exstar::MouseEvent*>* mouseEventsCopy = new exstar::ArrayList<exstar::MouseEvent*>();
		/**
		 * The deltaTime of the program
		*/
		double deltaTime = 0.0;
		/**
		 * The framerate of the program
		*/
		int frameRate = 16;
		/**
		 * state for whether the Camera will move on resize event
		*/
		bool adjustCameraOnResize = true;
		/**
		 * The size of the window
		*/
		exstar::Dimension size;
		/**
		 * The title of the window
		*/
		std::string title;
		/**
		 * The GLFW window
		*/
		GLFWwindow* window;

		/**
		 * The clock for calculating deltaTime
		*/
		exstar::Clock* clock;
		/**
		 * The color of the background
		*/
		double backgroundColor[4];

		//-------------Private Functions-------------
		/**
		 * Initiate OpenGL
		*/
		void initGL();
		/**
		 * The MainLoop
		 * called during run()
		*/
		void update();
		/**
		 * event called when window is resized
		 * adjusts the Graphics and the size variable
		 * 
		 * @param width New width of the window
		 * @param height New height of the window
		*/
		void resizeEvent(int width, int height);

		//-------------Static Functions-------------
		/**
		 * Used when OpenGL has an error
		*/
		static void error_callback(int error, const char* description);
		/**
		 * Used when OpenGL has a mouse event
		*/
		static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
		/**
		 * Used when OpenGL has a key event
		*/
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};

}
