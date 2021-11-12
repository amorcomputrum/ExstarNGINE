#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <ostream>

#include <Exceptions.hpp>

class Window {
public:
	Window(int width,int height,const char* title){
		this->width = width;
		this->height = height;
		this->title = title;
	}
	void run(){
		initGL();
		update();
		close();
	}
	void close(){
		glfwTerminate();
		glfwDestroyWindow(window);
	}
private:
	int width,height;
	const char* title;
	GLFWwindow* window;
	void initGL(){
		//set error callback
		glfwSetErrorCallback(error_callback);
		//init glfw
		if(!glfwInit()){
			throw exstar::exception("GLFW INIT ERROR: Well that failed quickly");
		}
		//init window
		window = glfwCreateWindow(width,height,title,NULL,NULL);
		if(!window){
			throw exstar::exception("GLFW WindowINIT ERROR: Well that failed too soon");
		}
		//show window
		glfwMakeContextCurrent(window);
	}
	void update(){
		while (!glfwWindowShouldClose(window))
		{
		    //Just keep on Swimming
		}
	}
	static void error_callback(int error, const char* description)
	{
	    fprintf(stderr, "Error: %s\n", description);
	}

};