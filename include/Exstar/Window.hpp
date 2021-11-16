#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
//include Libraries
#include <gl.c>
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <stb_image.h>

//include C++ libraries
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>
#if __WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//include Exstar Files
#include <Exstar/Utils/Math.hpp>
#include <Exstar/Utils/Key.hpp>
#include <Exstar/Utils/Exceptions.hpp>
#include <Exstar/Clock.hpp>
#include <Exstar/Utils/Dimension.hpp>
#include <Exstar/Camera.hpp>
#include <Exstar/Utils/ArrayList.hpp>
#include <Exstar/Utils/Point.hpp>
#include <Exstar/Utils/MouseEvent.hpp>

namespace exstar{
	class Window {
	public:
		Window(int width,int height,const char* title){
			size = exstar::Dimension{width,height};
			this->title = title;
			initGL();
		}
		//-------------Virtual Functions-------------
		virtual void render(Camera camera){
		}
		virtual void Update(double deltaTime){
		}
		virtual void onResize(int w,int h){
		}
		virtual void keyPressed(int key){
		}
		virtual void keyReleased(int key){
		}
		virtual void mousePressed(MouseEvent* event){
		}
		virtual void mouseReleased(MouseEvent* event){
		}
		//-------------Public Functions-------------
		void run(){
			//show window
			glfwMakeContextCurrent(window);
			gladLoadGL(glfwGetProcAddress);

			//set interval for buffer
			glfwSwapInterval(1);

			//allow Forward compatabilit with opengl
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

			//create clock
			clock = new exstar::Clock();

			//create camera
			camera = new exstar::Camera(size.width,size.height,0,0);
			//begin loop
			update();
			//close when loop closes
			close();
		}
		void close(){
			glfwDestroyWindow(window);
			glfwTerminate();
		}
		void setFramerate(int frameRate){
			this->frameRate = frameRate;
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
			size = exstar::Dimension{width,height};
			glfwSetWindowSize(window,width,height);
		}
		void setAdjustCameraOnResize(bool state){
			adjustCameraOnResize = state;
		}
		const char* getTitle(){
			return title;
		}
		bool isKeyPressed(int key){
			for(int i = 0; i < keysPressed->size;i++){
				if(key == keysPressed->get(i)){
					return true;
				}
			}
			return false;
		}
		exstar::Dimension getSize(){
			return size;
		}
		exstar::Point getMousePos(){
			double x,y;
			glfwGetCursorPos(window,&x,&y);
			return exstar::Point{(int)x,(int)y};
		}
		double DeltaTime(){
			return this->deltaTime;
		}
		int getMouseX(){
			double x,y;
			glfwGetCursorPos(window,&x,&y);
			return (int)x;
		}
		int getMouseY(){
			double x,y;
			glfwGetCursorPos(window,&x,&y);
			return (int)y;
		}
		int getWidth(){
			return size.width;
		}
		int getHeight(){
			return size.height;
		}
		bool getAdjustCameraOnResize(){
			return adjustCameraOnResize;
		}

	private:
		static ArrayList<int>* keysPressed;
		ArrayList<int>* keysPressedCopy = new ArrayList<int>();
		static ArrayList<exstar::MouseEvent*>* mouseEvents;
		ArrayList<exstar::MouseEvent*>* mouseEventsCopy = new ArrayList<exstar::MouseEvent*>();
		exstar::Dimension size;
		exstar::Point mousePos = exstar::Point{0,0};
		const char* title;
		GLFWwindow* window;
		exstar::Camera* camera;
		exstar::Clock* clock;
		double deltaTime = 0.0;
		int frameRate = 16;
		bool adjustCameraOnResize = true;
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
			glfwSetMouseButtonCallback(window, mouse_callback);
			//seed random
			srand(time(NULL));
		}
		void update(){
			double lastTime = glfwGetTime();
			while (!glfwWindowShouldClose(window))
			{
			    //Just keep on Swimming
				clock->start();
			    //clear frame
				glViewport(0, 0, size.width, size.height);
				glClear(GL_COLOR_BUFFER_BIT);
				Update(this->deltaTime);
				render((*camera));
			    //display frame
				glfwSwapBuffers(window);

				while(glfwGetTime() < lastTime + 1.0/frameRate){
					usleep(1000);
				}
				lastTime+=1.0/frameRate;
				this->deltaTime = clock->getTime()/1000;
				
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

				//check if a Mouse pressed
				for(int mp = 0; mp < mouseEvents->size; mp++){
					bool found = false;
					for(int mpc = 0; mpc < mouseEventsCopy->size; mpc++){
						if(mouseEventsCopy->get(mpc) == mouseEvents->get(mp)){
							//Mouse was pressed
							found = true;
						}
					}
					if(!found){
						//add mouseEvent to copy
						mouseEventsCopy->add(mouseEvents->get(mp));
						//call mousePressed event
						mouseEvents->get(mp)->pos.x+=camera->getX();
						mouseEvents->get(mp)->pos.y+=camera->getY();
						mousePressed(mouseEvents->get(mp));
					}
				}

				//check if a Mouse released
				for(int mpc = 0; mpc < mouseEventsCopy->size; mpc++){
					bool found = false;
					for(int mp = 0; mp < mouseEvents->size; mp++){
						if(mouseEventsCopy->get(mpc) == mouseEvents->get(mp)){
							//mouseEvent exists already
							found = true;
						}
					}
					if(!found){
						//call mouseReleased event
						mouseReleased(mouseEventsCopy->get(mpc));
						//remove mouseEvent from copy
						mouseEventsCopy->remove(mpc);
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
			size = exstar::Dimension{width,height};
			//call onResize event
			onResize(width,height);
		}

		//-------------Static Functions-------------
		static void error_callback(int error, const char* description)
		{
			fprintf(stderr, "EXSTAR GL ERROR: %s\n", description);
		}
		static void mouse_callback(GLFWwindow* window,int button,int action,int mods){
			if(action == GLFW_PRESS){
				bool found = false;
				// add to mouseEvents if not already there
				for(int i = 0; i < mouseEvents->size; i++){
					if(mouseEvents->get(i)->button == button){
						found = true;
						break;
					}
				}
				if(!found){
					double x,y;
					glfwGetCursorPos(window,&x,&y);
					mouseEvents->add(new exstar::MouseEvent{button,exstar::Point{(int)x,(int)y}});
				}
			}
			// was event a release
			else if(action == GLFW_RELEASE){
				//remove from mouseEvents
				for(int i = 0; i < mouseEvents->size; i++){
					if(mouseEvents->get(i)->button == button){
						mouseEvents->remove(i);
						break;
					}
				}
			}
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
	ArrayList<int>* exstar::Window::keysPressed = new ArrayList<int>();
	//initialize MouseEvents
	ArrayList<exstar::MouseEvent*>* exstar::Window::mouseEvents = new ArrayList<exstar::MouseEvent*>();
}