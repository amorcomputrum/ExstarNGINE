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
void exstar::Camera::drawEllipse(int x,int y,int rw,int rh){
	const char* vertexShaderSource = "#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"uniform mat4 ModelMatrix;\n"
									"uniform mat4 projection;\n"
									"void main()\n"
									"{\n"
									"	gl_Position = projection*(ModelMatrix*vec4(aPos,1.0f));\n"
									"}\0";
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);
	std::string fragmentShaderSourceString = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\n\tFragColor = vec4("+std::to_string(r)+","+std::to_string(g)+","+std::to_string(b)+","+std::to_string(a)+");\n}\0";
	const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
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

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float verticies[] = {0.5,-0.5,0.0,0.75,-0.5,0.0,0.6351,-0.2896,0.0,0.396,-0.2727,0.0,0.2525,-0.4647,0.0,0.3366,-0.6892,0.0,0.5709,-0.7397,0.0,0.74,-0.5699,0.0,0.6885,-0.3358,0.0,0.4636,-0.2527,0.0,0.2722,-0.397,0.0,0.2902,-0.636,0.0,0.5011,-0.75,0.0,0.711,-0.6341,0.0,0.7269,-0.395,0.0,0.5342,-0.2523,0.0,0.3101,-0.3374,0.0,0.2606,-0.572,0.0,0.4312,-0.7403,0.0,0.6651,-0.6877,0.0,0.7472,-0.4625,0.0,0.602,-0.2718,0.0,0.3631,-0.2908,0.0,0.25,-0.5022,0.0,0.3668,-0.7116,0.0,0.606,-0.7264,0.0,0.7478,
						-0.5331,0.0,0.6617,-0.3094,0.0,0.427,-0.2609,0.0,0.2593,-0.4323,0.0,0.313,-0.6659,0.0,0.5386,-0.747,0.0,0.7287,-0.601,0.0,0.7086,-0.3621,0.0,0.4967,-0.25,0.0,0.2879,-0.3677,0.0,0.2741,-0.607,0.0,0.468,-0.7479,0.0,0.6914,-0.6609,0.0,0.7388,-0.4259,0.0,0.5667,-0.2591,0.0,0.3333,-0.3137,0.0,0.2532,-0.5397,0.0,0.4,-0.7291,0.0,0.6388,-0.7079,0.0,0.75,-0.4956,0.0,0.6313,-0.2873,0.0,0.392,-0.2746,0.0,0.2519,-0.4691,0.0,0.34,-0.6921,0.0,0.5751,-0.7384,0.0,0.7412,-0.5656,0.0,0.6855,
						-0.3324,0.0,0.4593,-0.2533,0.0,0.2704,-0.401,0.0,0.2927,-0.6397,0.0,0.5055,-0.7499,0.0,0.7133,-0.6304,0.0,0.725,-0.391,0.0,0.5298,-0.2518,0.0,0.3072,-0.3408,0.0,0.2619,-0.5762,0.0,0.4355,-0.7415,0.0,0.6684,-0.6848,0.0,0.7465,-0.4582,0.0,0.598,-0.27,0.0,0.3594,-0.2933,0.0,0.2501,-0.5066,0.0,0.3706,-0.7139,0.0,0.61,-0.7245,0.0,0.7483,-0.5287,0.0,0.6583,-0.3065,0.0,0.4227,-0.2622,0.0,0.2582,-0.4365,0.0,0.316,-0.6692,0.0,0.5429,-0.7463,0.0,0.7304,-0.5969,0.0,0.7061,-0.3585,0.0,
						0.4923,-0.2501,0.0,0.2855,-0.3715,0.0,0.276,-0.611,0.0,0.4724,-0.7485,0.0,0.6942,-0.6575,0.0,0.7374,-0.4217,0.0,0.5624,-0.2579,0.0,0.33,-0.3167,0.0,0.2539,-0.544,0.0,0.4041,-0.7309,0.0,0.6424,-0.7055,0.0,0.7498,-0.4912,0.0,0.6275,-0.285,0.0,0.388,-0.2765,0.0,0.2514,-0.4735,0.0,0.3434,-0.6949,0.0,0.5794,-0.7371,0.0,0.7424,-0.5613,0.0,0.6825,-0.3292,0.0,0.4549,-0.2541,0.0,0.2687,-0.4051,0.0,0.2952,-0.6433,0.0,0.51,-0.7498,0.0,0.7156,-0.6266,0.0,0.723,-0.387,0.0,0.5254,-0.2513,
						0.0,0.3044,-0.3443,0.0,0.2633,-0.5804,0.0,0.4398,-0.7426,0.0,0.6716,-0.6818,0.0,0.7457,-0.4538,0.0,0.5939,-0.2683,0.0,0.3557,-0.2958,0.0,0.2502,-0.5111,0.0,0.3744,-0.7161,0.0,0.614,-0.7225,0.0,0.7488,-0.5243,0.0,0.6549,-0.3038,0.0,0.4185,-0.2636,0.0,0.2571,-0.4408,0.0,0.319,-0.6724,0.0,0.5473,-0.7455,0.0,0.7321,-0.5929,0.0,0.7035,-0.3548,0.0,0.4878,-0.2503,0.0,0.2833,-0.3753,0.0,0.278,-0.615,0.0,0.4768,-0.7489,0.0,0.6969,-0.654,0.0,0.736,-0.4175,0.0,0.5581,-0.2568,0.0,0.3268,
						-0.3197,0.0,0.2547,-0.5484,0.0,0.4082,-0.7325,0.0,0.6461,-0.7029,0.0,0.7496,-0.4867,0.0,0.6237,-0.2828,0.0,0.384,-0.2785,0.0,0.251,-0.4779,0.0,0.3469,-0.6976,0.0,0.5835,-0.7356,0.0,0.7434,-0.557,0.0,0.6795,-0.326,0.0,0.4505,-0.2549,0.0,0.2671,-0.4092,0.0,0.2977,-0.6469,0.0,0.5144,-0.7496,0.0,0.7178,-0.6228,0.0,0.721,-0.3831,0.0,0.521,-0.2509,0.0,0.3017,-0.3477,0.0,0.2647,-0.5846,0.0,0.4441,-0.7437,0.0,0.6748,-0.6787,0.0,0.7448,-0.4495,0.0,0.5898,-0.2667,0.0,0.3522,-0.2984,0.0,
						0.2505,-0.5155,0.0,0.3782,-0.7183,0.0,0.6179,-0.7204,0.0,0.7492,-0.5199,0.0,0.6514,-0.301,0.0,0.4144,-0.2651,0.0,0.2561,-0.4451,0.0,0.3221,-0.6756,0.0,0.5516,-0.7446,0.0,0.7337,-0.5887,0.0,0.7009,-0.3513,0.0,0.4834,-0.2506,0.0,0.2811,-0.3792,0.0,0.2801,-0.6189,0.0,0.4812,-0.7493,0.0,0.6996,-0.6505,0.0,0.7345,-0.4133,0.0,0.5538,-0.2559,0.0,0.3236,-0.3228,0.0,0.2556,-0.5527,0.0,0.4123,-0.7341,0.0,0.6496,-0.7003,0.0,0.7494,-0.4823,0.0,0.6199,-0.2806,0.0,0.3801,-0.2806,0.0,0.2506,
						-0.4823,0.0,0.3504,-0.7003,0.0,0.5877,-0.7341,0.0,0.7444,-0.5527,0.0,0.6764,-0.3228,0.0,0.4462,-0.2559,0.0,0.2655,-0.4133,0.0,0.3004,-0.6505,0.0,0.5188,-0.7493,0.0,0.7199,-0.6189,0.0,0.7189,-0.3792,0.0,0.5166,-0.2506,0.0,0.2991,-0.3513,0.0,0.2663,-0.5887,0.0,0.4484,-0.7446,0.0,0.6779,-0.6756,0.0,0.7439,-0.4451,0.0,0.5856,-0.2651,0.0,0.3486,-0.301,0.0,0.2508,-0.5199,0.0,0.3821,-0.7204,0.0,0.6218,-0.7183,0.0,0.7495,-0.5155,0.0,0.6478,-0.2984,0.0,0.4102,-0.2667,0.0,0.2552,-0.4495,
						0.0,0.3252,-0.6787,0.0,0.5559,-0.7437,0.0,0.7353,-0.5846,0.0,0.6983,-0.3477,0.0,0.479,-0.2509,0.0,0.279,-0.3831,0.0,0.2822,-0.6228,0.0,0.4856,-0.7496,0.0,0.7023,-0.6469,0.0,0.7329,-0.4092,0.0,0.5494,-0.2549,0.0,0.3205,-0.326,0.0,0.2566,-0.557,0.0,0.4165,-0.7356,0.0,0.6531,-0.6976,0.0,0.749,-0.4779,0.0,0.616,-0.2785,0.0,0.3763,-0.2828,0.0,0.2504,-0.4867,0.0,0.354,-0.7029,0.0,0.5918,-0.7325,0.0,0.7453,-0.5484,0.0,0.6732,-0.3197,0.0,0.4419,-0.2568,0.0,0.264,-0.4175,0.0,0.3031,
						-0.654,0.0,0.5232,-0.7489,0.0,0.722,-0.615,0.0,0.7167,-0.3753,0.0,0.5122,-0.2503,0.0,0.2965,-0.3549,0.0,0.2679,-0.5929,0.0,0.4527,-0.7455,0.0,0.681,-0.6724,0.0,0.7429,-0.4408,0.0,0.5814,-0.2636,0.0,0.3451,-0.3038,0.0,0.2512,-0.5243,0.0,0.386,-0.7225,0.0,0.6256,-0.7161,0.0,0.7498,-0.5111,0.0,0.6442,-0.2958,0.0,0.4061,-0.2683,0.0,0.2543,-0.4538,0.0,0.3284,-0.6818,0.0,0.5602,-0.7426,0.0,0.7367,-0.5804,0.0,0.6956,-0.3442,0.0,0.4746,-0.2513,0.0,0.277,-0.387,0.0,0.2844,-0.6266,0.0,
						0.4901,-0.7498,0.0,0.7048,-0.6433,0.0,0.7313,-0.4051,0.0,0.5451,-0.2541,0.0,0.3175,-0.3292,0.0,0.2576,-0.5613,0.0,0.4206,-0.7371,0.0,0.6566,-0.6949,0.0,0.7486,-0.4735,0.0,0.612,-0.2765,0.0,0.3724,-0.285,0.0,0.2502,-0.4912,0.0,0.3576,-0.7055,0.0,0.5959,-0.7309,0.0,0.7461,-0.544,0.0,0.67,-0.3167,0.0,0.4376,-0.2579,0.0,0.2626,-0.4217,0.0,0.3058,-0.6575,0.0,0.5276,-0.7485,0.0,0.724,-0.611,0.0,0.7144,-0.3715,0.0,0.5077,-0.2501,0.0,0.2939,-0.3585,0.0,0.2696,-0.597,0.0,0.4571,-0.7463,
						0.0,0.6841,-0.6692,0.0,0.7418,-0.4365,0.0,0.5772,-0.2622,0.0,0.3417,-0.3065,0.0,0.2517,-0.5287,0.0,0.39,-0.7245,0.0,0.6294,-0.7139,0.0,0.7499,-0.5066,0.0,0.6406,-0.2933,0.0,0.402,-0.27,0.0,0.2535,-0.4582,0.0,0.3316,-0.6848,0.0,0.5645,-0.7415,0.0,0.7381,-0.5762,0.0,0.6928,-0.3408,0.0,0.4702,-0.2518,0.0,0.275,-0.391,0.0,0.2867,-0.6304,0.0,0.4945,-0.7499,0.0,0.7073,-0.6397,0.0,0.7296,-0.401,0.0,0.5407,-0.2533,0.0,0.3145,-0.3324,0.0,0.2588,-0.5656,0.0,0.4249,-0.7384,0.0,0.66,-0.6921,
						0.0,0.7481,-0.4691,0.0,0.608,-0.2745,0.0,0.3687,-0.2873,0.0,0.25,-0.4956,0.0,0.3612,-0.7079,0.0,0.6,-0.7291,0.0,0.7468,-0.5396,0.0,0.6667,-0.3137,0.0,0.4333,-0.2591,0.0,0.2612,-0.4259,0.0,0.3087,-0.6609,0.0,0.532,-0.7479,0.0,0.7259,-0.607,0.0,0.7121,-0.3677,0.0,0.5033,-0.25,0.0,0.2914,-0.3621,0.0,0.2713,-0.601,0.0,0.4614,-0.747,0.0,0.687,-0.6659,0.0,0.7406,-0.4323,0.0,0.573,-0.2609,0.0,0.3383,-0.3094,0.0,0.2522,-0.5331,0.0,0.394,-0.7264,0.0,0.6332,-0.7116,0.0,0.75,-0.5022,0.0,
						0.6369,-0.2908,0.0,0.398,-0.2718,0.0,0.2528,-0.4625,0.0,0.3349,-0.6878,0.0,0.5688,-0.7403,0.0,0.7394,-0.572,0.0,0.6899,-0.3374,0.0,0.4658,-0.2523,0.0,0.2731,-0.395,0.0,0.289,-0.6341,0.0,0.4989,-0.75,0.0,0.7098,-0.636,0.0,0.7278,-0.397,0.0,0.5364,-0.2527,0.0,0.3115,-0.3358,0.0,0.26,-0.5699,0.0,0.4291,-0.7397,0.0,0.6634,-0.6892,0.0,0.7475,-0.4647,0.0,0.604,-0.2727,0.0,0.3649,-0.2896,0.0,0.25,-0.5,0.0,0.3649,-0.7104,0.0,0.604,-0.7273,0.0,0.7475,-0.5353,0.0,0.6634,-0.3108,0.0,};








	unsigned int indices[] = {0,1,2,0,3,2,0,4,3,0,5,4,0,6,5,0,7,6,0,8,7,0,9,8,0,10,9,0,11,10,0,12,11,0,13,12,0,14,13,0,15,14,0,16,15,0,17,16,0,18,17,0,19,18,0,20,19,0,21,20,0,22,21,0,23,22,0,24,23,0,25,24,0,26,25,0,27,26,0,28,27,0,29,28,0,30,29,0,31,30,0,32,31,0,33,32,0,34,33,0,35,34,0,36,35,0,37,36,0,38,37,0,39,38,0,40,39,0,41,40,0,42,41,0,43,42,0,44,43,0,45,44,0,46,45,0,47,46,0,48,47,0,49,48,0,50,49,0,51,50,0,52,51,0,53,52,0,54,53,0,55,54,0,56,55,0,57,56,0,58,57,0,59,58,0,60,59,0,61,60,0,62,61,0,63,
								62,0,64,63,0,65,64,0,66,65,0,67,66,0,68,67,0,69,68,0,70,69,0,71,70,0,72,71,0,73,72,0,74,73,0,75,74,0,76,75,0,77,76,0,78,77,0,79,78,0,80,79,0,81,80,0,82,81,0,83,82,0,84,83,0,85,84,0,86,85,0,87,86,0,88,87,0,89,88,0,90,89,0,91,90,0,92,91,0,93,92,0,94,93,0,95,94,0,96,95,0,97,96,0,98,97,0,99,98,0,100,99,0,101,100,0,102,101,0,103,102,0,104,103,0,105,104,0,106,105,0,107,106,0,108,107,0,109,108,0,110,109,0,111,110,0,112,111,0,113,112,0,114,113,0,115,114,0,116,115,0,117,116,0,
								118,117,0,119,118,0,120,119,0,121,120,0,122,121,0,123,122,0,124,123,0,125,124,0,126,125,0,127,126,0,128,127,0,129,128,0,130,129,0,131,130,0,132,131,0,133,132,0,134,133,0,135,134,0,136,135,0,137,136,0,138,137,0,139,138,0,140,139,0,141,140,0,142,141,0,143,142,0,144,143,0,145,144,0,146,145,0,147,146,0,148,147,0,149,148,0,150,149,0,151,150,0,152,151,0,153,152,0,154,153,0,155,154,0,156,155,0,157,156,0,158,157,0,159,158,0,160,159,0,161,160,0,162,161,0,163,162,0,164,163,0,165,
								164,0,166,165,0,167,166,0,168,167,0,169,168,0,170,169,0,171,170,0,172,171,0,173,172,0,174,173,0,175,174,0,176,175,0,177,176,0,178,177,0,179,178,0,180,179,0,181,180,0,182,181,0,183,182,0,184,183,0,185,184,0,186,185,0,187,186,0,188,187,0,189,188,0,190,189,0,191,190,0,192,191,0,193,192,0,194,193,0,195,194,0,196,195,0,197,196,0,198,197,0,199,198,0,200,199,0,201,200,0,202,201,0,203,202,0,204,203,0,205,204,0,206,205,0,207,206,0,208,207,0,209,208,0,210,209,0,211,210,0,212,211,
								0,213,212,0,214,213,0,215,214,0,216,215,0,217,216,0,218,217,0,219,218,0,220,219,0,221,220,0,222,221,0,223,222,0,224,223,0,225,224,0,226,225,0,227,226,0,228,227,0,229,228,0,230,229,0,231,230,0,232,231,0,233,232,0,234,233,0,235,234,0,236,235,0,237,236,0,238,237,0,239,238,0,240,239,0,241,240,0,242,241,0,243,242,0,244,243,0,245,244,0,246,245,0,247,246,0,248,247,0,249,248,0,250,249,0,251,250,0,252,251,0,253,252,0,254,253,0,255,254,0,256,255,0,257,256,0,258,257,0,259,258,0,260,
								259,0,261,260,0,262,261,0,263,262,0,264,263,0,265,264,0,266,265,0,267,266,0,268,267,0,269,268,0,270,269,0,271,270,0,272,271,0,273,272,0,274,273,0,275,274,0,276,275,0,277,276,0,278,277,0,279,278,0,280,279,0,281,280,0,282,281,0,283,282,0,284,283,0,285,284,0,286,285,0,287,286,0,288,287,0,289,288,0,290,289,0,291,290,0,292,291,0,293,292,0,294,293,0,295,294,0,296,295,0,297,296,0,298,297,0,299,298,0,300,299,0,301,300,0,302,301,0,303,302,0,304,303,0,305,304,0,306,305,0,307,306,0,
								308,307,0,309,308,0,310,309,0,311,310,0,312,311,0,313,312,0,314,313,0,315,314,0,316,315,0,317,316,0,318,317,0,319,318,0,320,319,0,321,320,0,322,321,0,323,322,0,324,323,0,325,324,0,326,325,0,327,326,0,328,327,0,329,328,0,330,329,0,331,330,0,332,331,0,333,332,0,334,333,0,335,334,0,336,335,0,337,336,0,338,337,0,339,338,0,340,339,0,341,340,0,342,341,0,343,342,0,344,343,0,345,344,0,346,345,0,347,346,0,348,347,0,349,348,0,350,349,0,351,350,0,352,351,0,353,352,0,354,353,0,355,354,
								0,356,355,0,357,356,0,358,357,0,359,358,0,360,359,0,360,1};
	unsigned int VBO,VAO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verticies),verticies,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//Transformations
	glm::mat4 projection;
	projection = glm::ortho(pos->x+0.0f,(float)size->width+pos->x,(float)size->height+pos->y,0.0f+pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(rw,rh,1.0f));

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,1080,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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