#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <iostream>
#include <ostream>

#include <Exceptions.hpp>
#include <Camera.hpp>

namespace exstar{
	class Window {
	public:
		Window(int width,int height,const char* title){
			this->width = width;
			this->height = height;
			this->title = title;
		}
		virtual void render(Camera camera){

		}
		void run(){
			initGL();
			update();
			close();
		}
		void close(){
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	private:
		int width,height;
		const char* title;
		GLFWwindow* window;
		Camera* camera;
		void initGL(){
			//set error callback
			glfwSetErrorCallback(error_callback);
			//init glfw
			if(!glfwInit()){
				throw exstar::exception("GLFW INIT ERROR: Well that failed quickly");
			}
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			//init window
			window = glfwCreateWindow(width,height,title,NULL,NULL);
			if(!window){
				throw exstar::exception("GLFW WindowINIT ERROR: Well that failed too soon");
			}
			//show window
			glfwMakeContextCurrent(window);
			gladLoadGL(glfwGetProcAddress);
			//set interval for buffer
			glfwSwapInterval(1);
			//create camera
			glfwGetFramebufferSize(window, &width, &height);

			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glViewport(0, 0, width, height);
			
			camera = new Camera(width,height,0,0);
		}
		void update(){
			while (!glfwWindowShouldClose(window))
			{
			    //Just keep on Swimming
			    //clear frame
			    glClear(GL_COLOR_BUFFER_BIT);
			    render((*camera));

			    //display frame
				glfwSwapBuffers(window);
				//get all events
				glfwPollEvents();
			}
		}
		static void error_callback(int error, const char* description)
		{
		    fprintf(stderr, "Error: %s\n", description);
		}

	};
}