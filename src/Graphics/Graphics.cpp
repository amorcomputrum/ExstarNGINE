#include "Exstar/exstarglad/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include "Exstar/Utils/Exception.h"
#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Graphics/Graphics.h"

exstar::Graphics::Graphics(int width,int height,int x,int y){
	pos = new exstar::Point{x,y};
	size = new exstar::Dimension{width,height};
	color = exstar::Color(0,0,0);
	loadData();
}
void exstar::Graphics::resize(int width,int height){
	size->width = width;
	size->height = height;
}
void exstar::Graphics::move(int x,int y){
	pos->x = pos->x + x;
	pos->y = pos->y + y;
}
void exstar::Graphics::set(int x,int y){
	pos->x -= pos->x - x;
	pos->y -= pos->y - y;
	
}
void exstar::Graphics::setColor(exstar::Color color){
	this->color = exstar::Color(color.r,color.g,color.b,color.a);
}
//-----------------------------DRAW SPRITE-----------------------------
void exstar::Graphics::drawSprite(exstar::Sprite sprite,int x,int y){
    //Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(sprite.getWidth(),sprite.getHeight(),1.0f));
	//Draw Sprite and cleanup
	glActiveTexture(GL_TEXTURE0);
	sprite.Bind();
	spriteShader.use();
	//Set uniforms
	spriteShader.uniformMat4("ModelMatrix",ModelMatrix);
	spriteShader.uniformMat4("projection",projection);
	glBindVertexArray(sprite.getVAO());
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}
void exstar::Graphics::drawSprite(exstar::Sprite sprite,exstar::Point pos){
	drawSprite(sprite,pos.x,pos.y);
}
//-----------------------------DRAW RECTANGLE-----------------------------
void exstar::Graphics::drawRect(int x,int y,int w,int h){
	//Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(w,h,1.0f));
	float r,g,b,a;
	r = exstar::Color::getFloat(color.r);
	g = exstar::Color::getFloat(color.g);
	b = exstar::Color::getFloat(color.b);
	a = exstar::Color::getFloat(color.a);
	glm::vec4 Color(r,g,b,a);
	this->shapeShader.use();
	//Set Uniforms
	this->shapeShader.uniformMat4("ModelMatrix",ModelMatrix);
	this->shapeShader.uniformMat4("projection",projection);
	this->shapeShader.uniformVec4("Color",Color);
	glBindVertexArray(*Rect.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN,0,4);
	glBindVertexArray(0);
}
void exstar::Graphics::drawRect(exstar::Point pos, exstar::Dimension size){
	drawRect(pos.x,pos.y,size.width,size.height);
}
void exstar::Graphics::drawRect(int x,int y, exstar::Dimension size){
	drawRect(x,y,size.width,size.height);
}
void exstar::Graphics::drawRect(exstar::Point pos, int w,int h){
	drawRect(pos.x,pos.y,w,h);
};

//-----------------------------DRAW ELLIPSE-----------------------------
void exstar::Graphics::drawEllipse(int x,int y,int w,int h){
	//Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(w/2,h/2,1.0f));
	float r,g,b,a;
	r = exstar::Color::getFloat(color.r);
	g = exstar::Color::getFloat(color.g);
	b = exstar::Color::getFloat(color.b);
	a = exstar::Color::getFloat(color.a);
	glm::vec4 Color(r,g,b,a);
	this->shapeShader.use();
	//Set Uniforms
	this->shapeShader.uniformMat4("ModelMatrix",ModelMatrix);
	this->shapeShader.uniformMat4("projection",projection);
	this->shapeShader.uniformVec4("Color",Color);
	glBindVertexArray(*Ellipse.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN,0,720);
	glBindVertexArray(0);
}
void exstar::Graphics::drawEllipse(exstar::Point pos, exstar::Dimension size){
	drawEllipse(pos.x,pos.y,size.width,size.height);
}
void exstar::Graphics::drawEllipse(int x,int y, exstar::Dimension size){
	drawEllipse(x,y,size.width,size.height);
}
void exstar::Graphics::drawEllipse(exstar::Point pos,int w,int h){
	drawEllipse(pos.x,pos.y,w,h);
}
//-----------------------------DRAW CIRCLE-----------------------------
void exstar::Graphics::drawCircle(int x,int y,int r){

	drawEllipse(x,y,r*2,r*2);
}
void exstar::Graphics::drawCircle(exstar::Point pos,int r){
	drawEllipse(pos.x,pos.y,r*2,r*2);
}
void exstar::Graphics::drawCircle(exstar::Vector2d pos,int r){
	drawEllipse(pos.x,pos.y,r*2,r*2);
}
//-----------------------------DRAW SHAPE-----------------------------
void exstar::Graphics::drawShape(exstar::Shape shape,int x,int y){
	//Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	float r,g,b,a;
	r = exstar::Color::getFloat(color.r);
	g = exstar::Color::getFloat(color.g);
	b = exstar::Color::getFloat(color.b);
	a = exstar::Color::getFloat(color.a);
	glm::vec4 Color(r,g,b,a);
	shapeShader.use();
	//Set uniforms
	shapeShader.uniformMat4("ModelMatrix",ModelMatrix);
	shapeShader.uniformMat4("projection",projection);
	shapeShader.uniformVec4("Color",Color);
	glBindVertexArray(*shape.getVAO());
	glDrawArrays(GL_TRIANGLE_FAN,0,shape.getSize());
	glBindVertexArray(0);
}
//-----------------------------DRAW LINE-----------------------------
void exstar::Graphics::drawLine(int x1,int y1,int x2,int y2){
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec2 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x,aPos.y,0.0f,1.0f);\n"
									 "}\0";
	//Pass Graphics's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color.r);
	g = exstar::Color::getFloat(color.g);
	b = exstar::Color::getFloat(color.b);
	a = exstar::Color::getFloat(color.a);
	//Create and Convert FragmentShaderSource to proper format
	std::string fragmentShaderSourceString = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\n\tFragColor = vec4("+std::to_string(r)+","+std::to_string(g)+","+std::to_string(b)+","+std::to_string(a)+");\n}\0";
	const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
	unsigned int shaderProgram,vertexShader,fragmentShader;
	//Create and Compile VertexShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	//Create and Compile FragmentShader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	//Create and Link ShaderProgram
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	//Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float vertices[] = {
		(float)(x1 - pos->x)/size->width*2.0 - 1.0,//x1
		-((float)(y1 - pos->y)/size->height*2.0 - 1.0),//y1
		(float)(x2 - pos->x)/size->width*2.0 - 1.0,//x2
		-((float)(y2 - pos->y)/size->height*2.0 - 1.0)//y2
		};
	unsigned int VBO, VAO;
	//Prepare Buffers
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	//Bind Buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glBindVertexArray(0);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES,0,2);
	glBindVertexArray(0);
	//Delete Buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}
void exstar::Graphics::drawLine(exstar::Point pos1,exstar::Point pos2){
	drawLine(pos1.x,pos1.y,pos2.x,pos2.y);
}
void exstar::Graphics::drawLine(exstar::Point pos1,exstar::Vector2d offset){
	drawLine(pos1.x,pos1.y,offset.getX(),offset.getY());
}
//-----------------------------DRAW PIXEL-----------------------------
void exstar::Graphics::drawPixel(int x,int y){
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec2 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x,aPos.y,0.0f,1.0f);\n"
									 "}\0";
	//Pass Graphics's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color.r);
	g = exstar::Color::getFloat(color.g);
	b = exstar::Color::getFloat(color.b);
	a = exstar::Color::getFloat(color.a);
	//Create and Convert FragmentShaderSource to proper format
	std::string fragmentShaderSourceString = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\n\tFragColor = vec4("+std::to_string(r)+","+std::to_string(g)+","+std::to_string(b)+","+std::to_string(a)+");\n}\0";
	const char* fragmentShaderSource = fragmentShaderSourceString.c_str();
	unsigned int shaderProgram,vertexShader,fragmentShader;
	//Create and Compile VertexShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	//Create and Compile FragmentShader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	//Create and Link ShaderProgram
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	//Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	float vertices[] = {
		(float)(x - pos->x)/size->width*2.0 - 1.0,//x
		-((float)((y - 1) - pos->y)/size->height*2.0 - 1.0)//y
		};
	unsigned int VBO, VAO;
	//Prepare Buffers
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	//Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//Postion Attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glBindVertexArray(0);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS,0,1);
	glBindVertexArray(0);
	//Delete Buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}
void exstar::Graphics::drawPixel(exstar::Point pos){
	drawPixel(pos.x,pos.y);
}
exstar::Dimension exstar::Graphics::getSize(){
	return *size;
}
int exstar::Graphics::getWidth(){
	return size->width;
}
int exstar::Graphics::getHeight(){
	return size->height;
}
int exstar::Graphics::getX(){
	return pos->x;
}
int exstar::Graphics::getY(){
	return pos->y;
}

void exstar::Graphics::loadData(){
	loadSpriteShader();
	loadShapeShader();
	loadRect();
	loadEllipse();
}
void exstar::Graphics::loadRect(){
	Rect = exstar::Graphics::Shader();
	float vertices[] = {
		1.0f,1.0f,
		1.0f,0.0f,
		0.0f,0.0f,
		0.0f,1.0f
	};
	glGenVertexArrays(1,Rect.getVAO());
	glGenBuffers(1,Rect.getVBO());

	glBindVertexArray(*Rect.getVAO());
	glBindBuffer(GL_ARRAY_BUFFER,*Rect.getVBO());
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
}
void exstar::Graphics::loadEllipse(){
	Ellipse = exstar::Graphics::Shader();
	float vertices[720];
	for(int i = 0;i < 720;i+=2){
		vertices[i] = 0.0f + (cos(i*(3.14*2)/360)*1.0);
		vertices[i+1] = 0.0f + (sin(i*(3.14*2)/360)*1.0);
	}
	glGenVertexArrays(1,Ellipse.getVAO());
	glGenBuffers(1,Ellipse.getVBO());

	glBindVertexArray(*Ellipse.getVAO());
	glBindBuffer(GL_ARRAY_BUFFER,*Ellipse.getVBO());
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
}
void exstar::Graphics::loadSpriteShader(){
	const std::string file =
	#include "Exstar/Graphics/Shaders/Sprite.glsl"
	;
	this->spriteShader = exstar::GLSL(file);
}

void exstar::Graphics::loadShapeShader(){
	const std::string file =
	#include "Exstar/Graphics/Shaders/Shape.glsl"
	;
	this->shapeShader = exstar::GLSL(file);
}

exstar::Graphics::Shader::Shader(){}
unsigned int* exstar::Graphics::Shader::getVAO(){
	return &VAO;
}
unsigned int* exstar::Graphics::Shader::getVBO(){
	return &VBO;
}