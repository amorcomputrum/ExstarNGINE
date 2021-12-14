#define GLFW_INCLUDE_NONE

#include "Exstar/Window.h"

//Window.h
exstar::Window::Window(int width,int height,std::string title){
	size = exstar::Dimension{width,height};
	this->title = title;
	camera = new exstar::Camera(size.width,size.height,0,0);
	initGL();
}

void exstar::Window::render(exstar::Camera camera){}
void exstar::Window::Update(double deltaTime){}
void exstar::Window::onResize(exstar::Dimension size){}
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

void exstar::Window::setTitle(std::string title){
	this->title = title;
	glfwSetWindowTitle(window,title.c_str());
}

void exstar::Window::setSizeLimits(int minW,int minH,int maxW,int maxH){
	glfwSetWindowSizeLimits(window,minW,minH,maxW,maxH);
}

void exstar::Window::setSize(int width, int height){
	size = exstar::Dimension{width,height};
	glfwSetWindowSize(window,width,height);
}
void exstar::Window::setSize(exstar::Dimension size){
	this->size = size;
	glfwSetWindowSize(window,size.width,size.height);
}

void exstar::Window::setAdjustCameraOnResize(bool state){
	adjustCameraOnResize = state;
}
void exstar::Window::setBackgroundColor(double r,double g,double b){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)){
		backgroundColor[0] = r/255.0;
		backgroundColor[1] = g/255.0;
		backgroundColor[2] = b/255.0;
		backgroundColor[3] = 1.0f;
	}else{
		throw exstar::exception("exstar::Window::setBackGroundColor - Out Of Range 0-255");
	}
	
}
void exstar::Window::setBackgroundColor(double r,double g,double b,double a){
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
void exstar::Window::moveCamera(int x,int y){
	camera->move(x,y);
}
void exstar::Window::moveCamera(exstar::Vector2d distance){
	camera->move(distance.getX(),distance.getY());
}
void exstar::Window::setCamera(int x,int y){
	camera->set(x,y);
}
void exstar::Window::setCamera(exstar::Point pos){
	camera->set(pos.x,pos.y);
}
std::string exstar::Window::getTitle(){
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//init window
	window = glfwCreateWindow(size.width,size.height,title.c_str(),NULL,NULL);
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
		glClearColor((float)backgroundColor[0],(float)backgroundColor[1],(float)backgroundColor[2],(float)backgroundColor[3]);
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
		camera->move(diffx/2,diffy/2);
		camera->resize(width,height);
	}
	//Update size
	size = exstar::Dimension{width,height};
	//call onResize event
	onResize(exstar::Dimension{width,height});
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
//Utils/Color.h
const exstar::Color exstar::Color::Black(0,0,0);
const exstar::Color exstar::Color::Red(255,0,0);
const exstar::Color exstar::Color::Green(0,255,0);
const exstar::Color exstar::Color::Blue(0,0,255);
const exstar::Color exstar::Color::White(255,255,255);
exstar::Color::Color(int r,int g,int b){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}else{
		throw exstar::exception("exstar::Color::Color - Out of Range 0-255");
	}
}
exstar::Color::Color(int r,int g,int b,int a){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255) && (a >= 0 && a <= 255)){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}else{
		throw exstar::exception("exstar::Color::Color - Out of Range 0-255");
	}
}
//Camera.h
exstar::Camera::Camera(int width,int height,int x,int y){
	pos = new exstar::Point{x,y};
	size = new exstar::Dimension{width,height};
	color = new exstar::Color(0,0,0);
}
void exstar::Camera::resize(int width,int height){
	size = new exstar::Dimension{width,height};
}
void exstar::Camera::move(int x,int y){
	pos->x = pos->x+x;
	pos->y = pos->y+y;
}
void exstar::Camera::set(int x,int y){
	pos->x += pos->x-x;
	pos->y += pos->y-y;
}
void exstar::Camera::setColor(exstar::Color color){
	this->color = new exstar::Color(color.r,color.g,color.b,color.a);
}
void exstar::Camera::drawSprite(exstar::Sprite* sprite,int x,int y){
	const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"layout (location = 2) in vec2 aTexCoord;\n"
	"out vec3 ourColor;\n"
	"out vec2 TexCoord;\n"
	"uniform mat4 ModelMatrix;\n"
	"uniform mat4 projection;\n"
	"void main()\n"
	"{\n"
	"gl_Position = projection*(ModelMatrix*vec4(aPos,1.0f));\n"
	"ourColor = aColor;\n"
	"TexCoord = aTexCoord;\n"
	"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColor;\n"
	"in vec2 TexCoord;\n"
	"uniform sampler2D ourTexture;\n"
	"void main()\n"
	"{\n"
	"	FragColor = texture(ourTexture, TexCoord);\n"
	"}\0";
	//Prepare and Compile Shaders
	unsigned int verexShader;
	verexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(verexShader,1,&vertexShaderSource,NULL);
	glCompileShader(verexShader);
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,verexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	//clean up
	glDeleteShader(verexShader);
	glDeleteShader(fragmentShader);
	//define params
	//XYZ,RGB,ST
	float vertices[] = {1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f};
	unsigned int indices[] = {0,1,3,1,2,3};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    // color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
    // texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
    // set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Load image according to its type(RGB,RGBA)
	if(sprite->getType() == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sprite->getTextureWidth(), sprite->getTextureHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, sprite->getImage());
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->getTextureWidth(), sprite->getTextureHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite->getImage());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
    //Transformations
	glm::mat4 projection;
	projection = glm::ortho(pos->x+0.0f,(float)size->width+pos->x,(float)size->height+pos->y,0.0f+pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(sprite->getWidth(),sprite->getHeight(),1.0f));
	//Draw image and cleanup
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void exstar::Camera::drawSprite(exstar::Sprite* sprite,exstar::Point pos){
	drawSprite(sprite,pos.x,pos.y);
}
void exstar::Camera::drawRect(int x,int y,int w,int h){
	const char* vertexShaderSource = "#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"layout (location = 1) in vec4 aColor;\n"
									"out vec4 ourColor;\n"
									"uniform mat4 ModelMatrix;\n"
									"uniform mat4 projection;\n"
									"void main()\n"
									"{\n"
									"	gl_Position = projection*(ModelMatrix*vec4(aPos,1.0f));\n"
									"	ourColor = aColor;\n"
									"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
										"out vec4 FragColor;\n"
										"in vec4 ourColor;\n"
										"void main()\n"
										"{\n"
										"	FragColor = ourColor;\n"
										"}\0";
	unsigned int shaderProgram,vertexShader,fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);
	float verticies[] = {
		1.0f,1.0f,0.0f,  r, g, b,a,
		1.0f,0.0f,0.0f, r, g, b,a,
		0.0f,0.0f,0.0f, r, g, b,a,
		0.0f,1.0f,0.0f,  r, g, b,a
	};
	unsigned int indices[] = {0,1,3,1,2,3};
	unsigned int VBO,VAO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verticies),verticies,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	//Transformations
	glm::mat4 projection;
	projection = glm::ortho(pos->x+0.0f,(float)size->width+pos->x,(float)size->height+pos->y,0.0f+pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(w,h,1.0f));

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	

}
void exstar::Camera::drawRect(exstar::Point pos, exstar::Dimension size){
	drawRect(pos.x,pos.y,size.width,size.height);
}
void exstar::Camera::drawRect(int x,int y, exstar::Dimension size){
	drawRect(x,y,size.width,size.height);
}
void exstar::Camera::drawRect(exstar::Point pos, int w,int h){
	drawRect(pos.x,pos.y,w,h);
}
exstar::Dimension exstar::Camera::getSize(){
	return *size;
}
int exstar::Camera::getWidth(){
	return size->width;
}
int exstar::Camera::getHeight(){
	return size->height;
}
int exstar::Camera::getX(){
	return pos->x;
}
int exstar::Camera::getY(){
	return pos->y;
}
//Sprite/Image_Handler.h
int* exstar::addImage(const char* file){
//load data
	int w,h,type;
	unsigned char * data = stbi_load(file,&w,&h,&type,0);
	if(!data){
		throw exstar::exception("Image is not in RGBA format");
	}
//check if already in images
	for(int i = 0; i < exstar::images->size; i++){
		if(exstar::images->get(i) == data){
			exstar::numUsers->replace(i,exstar::numUsers->get(i)+1);
			static int feedback[4];
			feedback[0] =  i;
			feedback[1] = w;
			feedback[2] = h;
			feedback[3] = type;
			return feedback;
		}
	}
	exstar::images->add(data);
	exstar::images->size;
	exstar::numUsers->add(1);
	static int feedback[4];
	feedback[0] =  exstar::images->size-1;
	feedback[1] = w;
	feedback[2] = h;
	feedback[3] = type;
	return feedback;
}

void exstar::removeImage(int index){
	if(exstar::numUsers->get(index) <= 0){
		stbi_image_free(exstar::images->get(index));
		exstar::images->remove(index);
		exstar::numUsers->remove(index);
	}
}

//Sprite/Sprite.h
exstar::Sprite::Sprite(const char* file){
	file = file;
	int* feedback = exstar::addImage(file);
	fileIndex = feedback[0];
	size = exstar::Dimension{feedback[1],feedback[2]};
	textureSize = exstar::Dimension{feedback[1],feedback[2]};
	type = feedback[3];
}
exstar::Sprite::~Sprite(){
	removeImage(fileIndex);
}
void exstar::Sprite::resize(int width,int height){
	size = exstar::Dimension{width,height};
}
void exstar::Sprite::resize(exstar::Dimension size){
	this->size = size;
}
int exstar::Sprite::getTextureWidth(){
	return textureSize.width;
}
int exstar::Sprite::getTextureHeight(){
	return textureSize.height;
}
exstar::Dimension exstar::Sprite::getTextureSize(){
	return textureSize;
}
int exstar::Sprite::getWidth(){
	return size.width;
}
int exstar::Sprite::getHeight(){
	return size.height;
}
exstar::Dimension exstar::Sprite::getSize(){
	return size;
}
int exstar::Sprite::getType(){
	return type;
}
unsigned char * exstar::Sprite::getImage(){
	return exstar::images->get(fileIndex);
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