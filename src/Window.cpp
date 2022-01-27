#define GLFW_INCLUDE_NONE

#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/Color.h"
#include "Exstar/Graphics/Sprite/stb_image.h"
#include "Exstar/Utils/Exception.h"

#include "Exstar/Window.h"

exstar::Window::Window(int width, int height, std::string title){
	size        = exstar::Dimension{width, height};
	this->title = title;
	initGL();
	g           = new exstar::Graphics(size.width, size.height, 0, 0);
}

//Virtual Functions
void exstar::Window::render(exstar::Graphics g){}
void exstar::Window::Update(double deltaTime){}
void exstar::Window::onResize(exstar::Dimension size){}
void exstar::Window::keyPressed(int key){}
void exstar::Window::keyReleased(int key){}
void exstar::Window::mousePressed(MouseEvent* event){}
void exstar::Window::mouseReleased(MouseEvent* event){}

void exstar::Window::run(){
	//show window
	glfwShowWindow(window);
	//set interval for buffer
	glfwSwapInterval(1);
	//allow Forward compatability with opengl
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE                 );
	glfwWindowHint(GLFW_OPENGL_PROFILE       , GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES              , 2                       );

	glEnable(GL_MULTISAMPLE); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	//create clock
	clock = new exstar::Clock(); 
	//begin loop
	update();
	//close when loop closes
	close();
}

void exstar::Window::close(){
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(1);
}

void exstar::Window::setBufferCount(int count){
	glfwSwapInterval(count);
}

void exstar::Window::setFramerate(int frameRate){
	this->frameRate = frameRate;
}

void exstar::Window::setIcon(const char* path){
	GLFWimage images[1];
	images[0].pixels = stbi_load(path, &images[0].width, &images[0].height, 0, 4);
	glfwSetWindowIcon(window, 1, images); 
	stbi_image_free(images[0].pixels);
}

void exstar::Window::setTitle(std::string title){
	this->title = title;
	glfwSetWindowTitle(window, title.c_str());
}

void exstar::Window::setSizeLimits(int minW, int minH, int maxW, int maxH){
	glfwSetWindowSizeLimits(window, minW, minH, maxW, maxH);
}

void exstar::Window::setSize(int width, int height){
	size = exstar::Dimension{ width, height};
	glfwSetWindowSize(window, width, height);
}

void exstar::Window::setSize(exstar::Dimension size){
	this->size = size;
	glfwSetWindowSize(window, size.width, size.height);
}

void exstar::Window::setAdjustCameraOnResize(bool state){
	adjustCameraOnResize = state;
}

void exstar::Window::setBackgroundColor(double r, double g, double b){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)){
		backgroundColor[0] = r/255.0;
		backgroundColor[1] = g/255.0;
		backgroundColor[2] = b/255.0;
		backgroundColor[3] = 1.0f   ;
	}else{
		throw exstar::exception("exstar::Window::setBackGroundColor - Out Of Range 0-255");
	}
}

void exstar::Window::setBackgroundColor(double r, double g, double b, double a){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255) && (a >= 0 && a <= 255)){
		backgroundColor[0] = r/255.0;
		backgroundColor[1] = g/255.0;
		backgroundColor[2] = b/255.0;
		backgroundColor[3] = a/255.0;
	}else{
		throw exstar::exception("exstar::Window::setBackGroundColor - Out Of Range 0-255");
	}
}

void exstar::Window::setBackgroundColor(exstar::Color color){
	backgroundColor[0] = exstar::Color::getFloat(color.r);
	backgroundColor[1] = exstar::Color::getFloat(color.g);
	backgroundColor[2] = exstar::Color::getFloat(color.b);
	backgroundColor[3] = exstar::Color::getFloat(color.a);
}

void exstar::Window::moveCamera(int x, int y){
	g->move(x, y);
}

void exstar::Window::moveCamera(exstar::Vector2d distance){
	g->move(distance.x, distance.y);
}

void exstar::Window::setCamera(int x, int y){
	g->set(x, y);
}

void exstar::Window::setCamera(exstar::Point pos){
	g->set(pos.x, pos.y);
}

void exstar::Window::setCameraCenter(int x, int y){
	g->set(x - size.width/2, y - size.height/2);
}

void exstar::Window::setCameraCenter(exstar::Point pos){
	setCameraCenter(pos.x, pos.y);
}

void exstar::Window::setCameraCenter(exstar::Vector2d pos){
	setCameraCenter(pos.x, pos.y);
}

std::string exstar::Window::getTitle(){
	return title;
}

bool exstar::Window::isKeyPressed(int key){
	for(int i = 0; i < keysPressed->size; i++){
		if(key == keysPressed->get(i)){
			return true;
		}
	}
	return false;
}

exstar::Dimension exstar::Window::getSize(){
	return size;
}

exstar::Point exstar::Window::getMousePos(){
	double x,y;
	glfwGetCursorPos(window, &x, &y);
	return exstar::Point{(int)x, (int)y};
}

double exstar::Window::DeltaTime(){
	return this->deltaTime;
}

int exstar::Window::getMouseX(){
	double x,y;
	glfwGetCursorPos(window, &x, &y);
	return (int)x;
}

int exstar::Window::getMouseY(){
	double x,y;
	glfwGetCursorPos(window, &x, &y);
	return (int)y;
}

int exstar::Window::getWidth(){
	return size.width;
}

int exstar::Window::getHeight(){
	return size.height;
}

bool exstar::Window::getAdjustCameraOnResize(){
	return adjustCameraOnResize;
}

//PRIVATE 
//exstar::Window Vars initialize
exstar::ArrayList<int>*                 exstar::Window::keysPressed = new exstar::ArrayList<int>()                ;
exstar::ArrayList<exstar::MouseEvent*>* exstar::Window::mouseEvents = new exstar::ArrayList<exstar::MouseEvent*>();

void exstar::Window::initGL(){
	//set error callback
	glfwSetErrorCallback(error_callback);
	//init glfw
	if(!glfwInit()){
		throw exstar::exception("GLFW INIT ERROR: Well that failed quickly"       );
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//init window
	window = glfwCreateWindow(size.width, size.height, title.c_str(), NULL, NULL);
	if(!window){
		throw exstar::exception("GLFW WindowINIT ERROR: Well that failed too soon");
	}
	//setCallbacks for window
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_callback);
	//seed random
	srand(time(NULL));
	//Set WindowBackground Color
	setBackgroundColor(exstar::Color::Black);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwHideWindow(window);
}

void exstar::Window::update(){
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
	    //Just keep on Swimming
		clock->start();
	    //clear frame
		glViewport(0, 0, size.width, size.height);
		glClearColor((float)backgroundColor[0], (float)backgroundColor[1], (float)backgroundColor[2], (float)backgroundColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		Update(this->deltaTime);
		render(*g);
	    //display frame
		glfwSwapBuffers(window);
		while(glfwGetTime() < lastTime + 1.0/frameRate){
			#if defined(__WIN32) || defined(_WIN64)
				sleep( (lastTime + 1.0/frameRate) - glfwGetTime());
			#else
				usleep((lastTime + 1.0/frameRate) - glfwGetTime());
			#endif
		}
		lastTime += 1.0/frameRate;
		this->deltaTime = clock->getTime()/1000;
		
		//check if resized
		int w,h;
		glfwGetFramebufferSize(window, &w, &h);
		if(w != size.width || h != size.height){
			resizeEvent(w, h);
		}
		//check if a key pressed
		for(int kp = 0; kp < keysPressed->size; kp++){
			bool found  = false;
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
			bool found  = false;
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
				mouseEvents->get(mp)->pos.x += g->getX();
				mouseEvents->get(mp)->pos.y += g->getY();
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

void exstar::Window::resizeEvent(int width, int height){
	if(adjustCameraOnResize){
		//get difference in size, then adjust Camera pos
		int diffx = size.width - width;
		int diffy = size.height - height;
		g->move(diffx/2, diffy/2);
		g->resize(width, height);
	}
	//call onResize event
	onResize(exstar::Dimension{width, height});
	//Update size
	size = exstar::Dimension{width, height   };
	
}

//Static
void exstar::Window::error_callback(int error, const char* description){
	fprintf(stderr, "EXSTAR GL ERROR: %s\n", description);
}

void exstar::Window::mouse_callback(GLFWwindow* window, int button, int action, int mods){
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
			glfwGetCursorPos(window, &x, &y);
			mouseEvents->add(new exstar::MouseEvent{button,exstar::Point{(int)x, (int)y}});
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

void exstar::Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
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