#define GLFW_INCLUDE_NONE
//include Libraries
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <stb_image.h>

//include C++ libraries
#include <iostream>
#include <ostream>

//include Exstar Files
#include <Key.hpp>
#include <Exceptions.hpp>
#include <Camera.hpp>
#include <Dimension.hpp>
#include <ArrayList.hpp>

namespace exstar{
	class Window {
	public:
		
		Window(int width,int height,const char* title){
			size = Dimension{width,height};
			this->title = title;
		}
		//-------------Virtual Functions-------------
		virtual void render(Camera camera){
		}
		virtual void onResize(int w,int h){
		}
		virtual void keyPressed(int key){
		}
		virtual void keyReleased(int key){
		}
		//-------------Public Functions-------------
		void run(){
			initGL();
			update();
			close();
		}
		void close(){
			glfwDestroyWindow(window);
			glfwTerminate();
		}
		void setIcon(const char* path){
			GLFWimage images[1];
			images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);
			glfwSetWindowIcon(window, 1, images); 
			stbi_image_free(images[0].pixels);
		}
		void setTitle(const char* title){
			glfwSetWindowTitle(window,title);
		}
		void setSizeLimits(int minW,int minH,int maxW,int maxH){
			glfwSetWindowSizeLimits(window,minW,minH,maxW,maxH);
		}
		void setSize(int width, int height){
			size = Dimension{width,height};
			glfwSetWindowSize(window,width,height);
		}
	private:
		static ArrayList<int>* keysPressed;
		ArrayList<int>* keysPressedCopy = new ArrayList<int>();
		Dimension size;
		const char* title;
		GLFWwindow* window;
		Camera* camera;
		bool adjustCameraOnResize = false;
		//-------------Private Functions-------------
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
			window = glfwCreateWindow(size.width,size.height,title,NULL,NULL);
			if(!window){
				throw exstar::exception("GLFW WindowINIT ERROR: Well that failed too soon");
			}

			//setCallbacks for window
			glfwSetKeyCallback(window, key_callback);

			//show window
			glfwMakeContextCurrent(window);
			gladLoadGL(glfwGetProcAddress);

			//set interval for buffer
			glfwSwapInterval(1);

			//allow Forward compatabilit with opengl
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			//create camera
			camera = new Camera(size.width,size.height,0,0);
		}
		void update(){
			while (!glfwWindowShouldClose(window))
			{
			    //Just keep on Swimming
			    //clear frame
			    glViewport(0, 0, size.width, size.height);
			    glClear(GL_COLOR_BUFFER_BIT);
			    render((*camera));

			    //display frame
				glfwSwapBuffers(window);

				//check if resized
				int w,h;
				glfwGetFramebufferSize(window, &w, &h);
				if(w != size.width || h != size.height){
					resizeEvent(w,h);
				}

				//check if a key pressed
				for(int kp = 0; kp < keysPressed->size; kp++){
					bool found = false;
					for(int kpc = 0; kpc < keysPressedCopy->size; kpc++){
						if(keysPressedCopy->get(kpc) == keysPressed->get(kp)){
							//key was pressed
							found = true;
						}
					}
					if(!found){
						//add key to copy
						keysPressedCopy->add(keysPressed->get(kp));
						//call keyPressed event
						keyPressed(keysPressed->get(kp));
					}
				}

				//check if a key released
				for(int kpc = 0; kpc < keysPressedCopy->size; kpc++){
					bool found = false;
					for(int kp = 0; kp < keysPressed->size; kp++){
						if(keysPressedCopy->get(kpc) == keysPressed->get(kp)){
							//key exists already
							found = true;
						}
					}
					if(!found){
						//call keyReleased event
						keyReleased(keysPressedCopy->get(kpc));
						//remove key from copy
						keysPressedCopy->remove(kpc);
					}
				}
				//get all events
				glfwPollEvents();
			}
			//Stop Swimming
		}
		void resizeEvent(int width, int height){
			if(adjustCameraOnResize){
				//get difference in size, then adjust camera pos
				int diffx = size.width-width;
				int diffy = size.height-height;
				camera->move(diffx,diffy);
				camera->resize(width,height);
			}
			//Update size
			size = Dimension{width,height};
			//call onResize event
			onResize(width,height);
		}

		//-------------Static Functions-------------
		static void error_callback(int error, const char* description)
		{
		    fprintf(stderr, "EXSTAR GL ERROR: %s\n", description);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
			//was event a press
			if(action == GLFW_PRESS){
				bool found = false;
				// add to keysPressed if not already there
				for(int i = 0; i < keysPressed->size; i++){
					if(keysPressed->get(i) == key){
						found = true;
						break;
					}
				}
				if(!found){
					keysPressed->add(key);
				}
			}
			// was event a release
			else if(action == GLFW_RELEASE){
				//remove from keysPressed
				for(int i = 0; i < keysPressed->size; i++){
					if(keysPressed->get(i) == key){
						keysPressed->remove(i);
						break;
					}
				}
			}
		}
	};
	//initialize keysPressed
	ArrayList<int>* Window::keysPressed = new ArrayList<int>();
}