#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <gl.c>
#include "Exstar/Window.h"

//Window.h
exstar::Window::Window(int width,int height,const char* title){
	size = exstar::Dimension{width,height};
	this->title = title;
	initGL();
}
void exstar::Window::render(Camera camera){}
void exstar::Window::Update(double deltaTime){}
void exstar::Window::onResize(int w,int h){}
void exstar::Window::keyPressed(int key){}
void exstar::Window::keyReleased(int key){}
void exstar::Window::mousePressed(MouseEvent* event){}
void exstar::Window::mouseReleased(MouseEvent* event){}
void exstar::Window::run(){
	//show window
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	//set interval for buffer
	glfwSwapInterval(1);

	//allow Forward compatability with opengl
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

void exstar::Window::close(){
	glfwDestroyWindow(window);
	glfwTerminate();
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

void exstar::Window::setTitle(const char* title){
	glfwSetWindowTitle(window,title);
}

void exstar::Window::setSizeLimits(int minW,int minH,int maxW,int maxH){
	glfwSetWindowSizeLimits(window,minW,minH,maxW,maxH);
}

void exstar::Window::setSize(int width, int height){
	size = exstar::Dimension{width,height};
	glfwSetWindowSize(window,width,height);
}

void exstar::Window::setAdjustCameraOnResize(bool state){
	adjustCameraOnResize = state;
}
const char* exstar::Window::getTitle(){
	return title;
}
bool exstar::Window::isKeyPressed(int key){
	for(int i = 0; i < keysPressed->size;i++){
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
	glfwGetCursorPos(window,&x,&y);
	return exstar::Point{(int)x,(int)y};
}

double exstar::Window::DeltaTime(){
	return this->deltaTime;
}

int exstar::Window::getMouseX(){
	double x,y;
	glfwGetCursorPos(window,&x,&y);
	return (int)x;
}

int exstar::Window::getMouseY(){
	double x,y;
	glfwGetCursorPos(window,&x,&y);
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
exstar::ArrayList<int>* exstar::Window::keysPressed = new exstar::ArrayList<int>();
exstar::ArrayList<exstar::MouseEvent*>* exstar::Window::mouseEvents = new exstar::ArrayList<exstar::MouseEvent*>();

void exstar::Window::initGL(){
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

void exstar::Window::update(){
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

void exstar::Window::resizeEvent(int width, int height){
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
//Static
void exstar::Window::error_callback(int error, const char* description){
	fprintf(stderr, "EXSTAR GL ERROR: %s\n", description);
}
void exstar::Window::mouse_callback(GLFWwindow* window,int button,int action,int mods){
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
//Public
//Clock.h
exstar::Clock::Clock(){
	start();
}
void exstar::Clock::start(){
	time = std::chrono::high_resolution_clock::now();
}
double exstar::Clock::getTime(){
	return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-time).count();
}
//Camera.h
exstar::Camera::Camera(int width,int height,int x,int y){
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
}
void exstar::Camera::resize(int width,int height){
	this->width = width;
	this->height = height;
}
void exstar::Camera::move(int x,int y){
	this->x+=x;
	this->y+=y;
}
void exstar::Camera::set(int x,int y){
	this->x += this->x-x;
	this->y += this->y-y;
}
exstar::Dimension exstar::Camera::getSize(){
	return Dimension{this->width,this->height};
}
int exstar::Camera::getWidth(){
	return this->width;
}
int exstar::Camera::getHeight(){
	return this->height;
}
int exstar::Camera::getX(){
	return x;
}
int exstar::Camera::getY(){
	return y;
}

int exstar::addImage(const char* file,int w,int h){
	//load data
	unsigned char * data = stbi_load(file,&this.w,&this.h,4,STBI_rgb_alpha);
	if(data == nullptr){
		throw exstar::exception("Image is not in RGBA format");
	}
	//check if already in images
	for(int i = 0; i < exstar::images->size; i++){
		if(exstar::images->get(i) == data){
			exstar::numUsers->replace(i,exstar::numUsers->get()+1);
			return i;
		}
	}
	exstar::images->add(data);
	exstar::numUsers->add(1);
	return images->size-1;
}

void exstar::removeImage(int index){
	exstar::images->replace(index,exstar::images->get(index)-1);
	if(exstar::numUsers->get(index) <= 0){
		exstar::images->remove(index);
	}
}

//Sprite.h
exstar::Sprite(const char* file,int w,int h){
	this.x = 0;
	this.y = 0;
	this.w = w;
	this.h = h;
	index = exstar::addImage(file);
}
exstar::Sprite(const char* file,int x,int y,int w,int h){
	this.x = x;
	this.y = y;
	this.w = w;
	this.h = h;
	index = exstar::addImage(file);
}
~exstar::Sprite(){
	removeImage(index);
}

//Utils/ArrayList.h
template<class T>
exstar::ArrayList<T>::ArrayList(){
	size = 0;
	this->exstar::ArrayList<T>::data.clear();
}
template <class T>
void exstar::ArrayList<T>::add(T n){
	this->exstar::ArrayList<T>::data.push_back(n);
	size++;
}
template <class T>
void exstar::ArrayList<T>::replace(int i,T n){
	this->exstar::ArrayList<T>::data[i] = n;
}
template <class T>
void exstar::ArrayList<T>::remove(int i){
	this->exstar::ArrayList<T>::data.erase(this->data.begin()+i);
	size--;
}

template <class T>
T exstar::ArrayList<T>::get(int g){
	if(g > -1 && g < size){
		return this->data[g];
	}else{
		throw std::invalid_argument("Out of Range");
	}
};
//Utils/Exceptions
exstar::exception::exception(std::string message){
	std::cerr << message << std::endl;
}

//Utils/Math.h
double exstar::Distance(double x1,double y1,double x2, double y2){
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

int exstar::Random(int min,int max){
	return rand() % (max - min +1)+min;
}
//Utils/Vector2d.h
exstar::Vector2d::Vector2d(int x,int y){
	data[0] = x;
	data[1] = y;
}
float exstar::Vector2d::dot(exstar::Vector2d v){
	return (getX()*v.getY()) + (v.getX() * getY());
}
float exstar::Vector2d::magnitude(){
	return std::sqrt((data[0]*data[0])+(data[1]*data[1]));
}
void exstar::Vector2d::add(exstar::Vector2d vec){
	data[0] += vec.getX();
	data[1] += vec.getY();
}
void exstar::Vector2d::add(int x,int y){
	data[0] += x;
	data[1] += y;
}
void exstar::Vector2d::min(exstar::Vector2d vec){
	data[0] -= vec.getX();
	data[1] -= vec.getY();
}
void exstar::Vector2d::min(int x,int y){
	data[0] -= x;
	data[1] -= y;
}
void exstar::Vector2d::mul(exstar::Vector2d vec){
	data[0] *= vec.getX();
	data[1] *= vec.getY();
}
void exstar::Vector2d::mul(int x,int y){
	data[0] *= x;
	data[1] *= y;
}
void exstar::Vector2d::div(exstar::Vector2d vec){
	data[0] /= vec.getX();
	data[1] /= vec.getY();
}
void exstar::Vector2d::div(int x,int y){
	data[0] /= x;
	data[1] /= y;
}
void exstar::Vector2d::set(int x,int y){
	data[0] = x;
	data[1] = y;
}
int exstar::Vector2d::getX(){
	return data[0];
}
int exstar::Vector2d::getY(){
	return data[1];
}