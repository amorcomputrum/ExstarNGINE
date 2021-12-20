#include "Exstar/exstarglad/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include "Exstar/Utils/Exception.h"
#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Graphics/Camera.h"

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
//-----------------------------DRAW SPRITE-----------------------------
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
	//Create and Compile VertexShader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	//Create and Compile FragmentShader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	//Create and Link ShaderProgram
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);
	//Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//Define the sides of the sprite to load
	float lx,ty,rx,by;
	lx = sprite->getPos().x/sprite->getTextureSize().width;
	ty = sprite->getPos().y/sprite->getTextureSize().height;
	rx = (sprite->getPos().x + sprite->getCut().width)/sprite->getTextureSize().width;
	by = (sprite->getPos().y + sprite->getCut().height)/sprite->getTextureSize().height;
	//XYZ,RGB,ST
	float vertices[] = {
		1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,rx,by,//top-right
		1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,rx,ty,//bottom-right
		0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,lx,ty,//bottom-left
		0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,lx,by//top-left
		};

	unsigned int indices[] = {0,1,3,1,2,3};
	//Prepare Buffers
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	//Bind Buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    // position attribute
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
    // color attribute
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
    // texture coord attribute
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
	//Load Texture
	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
    // set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //Load Sprite according to its type(RGB,RGBA)
	if(sprite->getType() == 3){
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,sprite->getTextureWidth(),sprite->getTextureHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,sprite->getImage());
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,sprite->getTextureWidth(),sprite->getTextureHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,sprite->getImage());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
    //Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(sprite->getWidth(),sprite->getHeight(),1.0f));
	//Draw Sprite and cleanup
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
	//Set uniforms
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
	//Delete Buffers
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&EBO);
}
void exstar::Camera::drawSprite(exstar::Sprite* sprite,exstar::Point pos){
	drawSprite(sprite,pos.x,pos.y);
}
//-----------------------------DRAW RECTANGLE-----------------------------
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
	//Create and Compile VertexShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	//Create and Compile Fragment Shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	//Create and Link ShaderProgram
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//Pass Camera's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);

	float vertices[] = {
		1.0f,1.0f,0.0f,  r, g, b,a,
		1.0f,0.0f,0.0f, r, g, b,a,
		0.0f,0.0f,0.0f, r, g, b,a,
		0.0f,1.0f,0.0f,  r, g, b,a
		};

	unsigned int indices[] = {0,1,3,1,2,3};
	//Prepare Buffers
	unsigned int VBO,VAO,EBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	//Bind Buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	//Position attributes
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//Color attributes
	glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(w,h,1.0f));
	glUseProgram(shaderProgram);
	//Set Uniforms
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
	//Delete Buffers
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
};
//-----------------------------DRAW ELLIPSE-----------------------------
void exstar::Camera::drawEllipse(int x,int y,int w,int h){
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "uniform mat4 ModelMatrix;\n"
									 "uniform mat4 projection;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = projection*(ModelMatrix*vec4(aPos,1.0f));\n"
									 "}\0";
	//Pass Camera's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);
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
	//360 degrees of verticies to render
	float vertices[] = {
		0.5,0.5,0.0,1.0,0.5,0.0,0.7702,0.9207,0.0,0.2919,0.9546,0.0,0.005,0.5706,0.0,0.1732,0.1216,0.0,0.6418,0.0205,0.0,0.9801,0.3603,0.0,0.877,0.8285,0.0,0.4272,0.9947,0.0,0.0444,0.7061,0.0,0.0805,0.228,0.0,0.5022,0.0,0.0,0.9219,0.2317,0.0,0.9537,0.7101,0.0,0.5684,0.9953,0.0,0.1202,0.8251,0.0,0.0212,0.356,0.0,0.3624,0.0193,0.0,0.8302,0.1245,0.0,0.9944,0.5749,0.0,0.704,0.9565,0.0,0.2261,0.9183,0.0,0.0,0.4956,0.0,0.2336,0.0769,0.0,0.7121,0.0472,0.0,0.9956,0.4338,0.0,0.8235,0.8813,
		0.0,0.3539,0.9782,0.0,0.0187,0.6355,0.0,0.126,0.1682,0.0,0.5771,0.006,0.0,0.9574,0.298,0.0,0.9171,0.7757,0.0,0.4934,1.0,0.0,0.0757,0.7645,0.0,0.0482,0.2859,0.0,0.436,0.0041,0.0,0.8827,0.1782,0.0,0.9775,0.6482,0.0,0.6333,0.9819,0.0,0.1665,0.8726,0.0,0.0063,0.4207,0.0,0.3,0.0417,0.0,0.7776,0.0841,0.0,0.9999,0.5089,0.0,0.7627,0.9255,0.0,0.2839,0.9509,0.0,0.0038,0.5618,0.0,0.1799,0.1159,0.0,0.6503,0.0231,0.0,0.9825,0.3688,0.0,0.8711,0.8351,0.0,0.4185,0.9933,0.0,0.0409,0.698,
		0.0,0.0853,0.2206,0.0,0.5111,0.0001,0.0,0.9266,0.2392,0.0,0.9499,0.7181,0.0,0.5596,0.9964,0.0,0.1145,0.8184,0.0,0.0238,0.3476,0.0,0.3709,0.0169,0.0,0.8368,0.1304,0.0,0.9929,0.5837,0.0,0.6959,0.96,0.0,0.2188,0.9134,0.0,0.0002,0.4867,0.0,0.2411,0.0722,0.0,0.7201,0.051,0.0,0.9967,0.4426,0.0,0.8167,0.8869,0.0,0.3455,0.9755,0.0,0.0164,0.6269,0.0,0.1319,0.1616,0.0,0.5859,0.0074,0.0,0.9609,0.3061,0.0,0.9122,0.7831,0.0,0.4845,0.9998,0.0,0.0711,0.757,0.0,0.052,0.2779,0.0,0.4448,
		0.0031,0.0,0.8883,0.1851,0.0,0.9748,0.6566,0.0,0.6248,0.9842,0.0,0.16,0.8666,0.0,0.0078,0.412,0.0,0.3082,0.0383,0.0,0.7849,0.0891,0.0,0.9997,0.5177,0.0,0.7551,0.93,0.0,0.276,0.947,0.0,0.0028,0.553,0.0,0.1868,0.1103,0.0,0.6587,0.0259,0.0,0.9847,0.3774,0.0,0.8651,0.8416,0.0,0.4098,0.9918,0.0,0.0374,0.6898,0.0,0.0904,0.2133,0.0,0.5199,0.0004,0.0,0.9312,0.2468,0.0,0.946,0.726,0.0,0.5508,0.9974,0.0,0.1089,0.8115,0.0,0.0266,0.3392,0.0,0.3795,0.0147,0.0,0.8432,0.1364,0.0,0.9914,
		0.5924,0.0,0.6878,0.9634,0.0,0.2115,0.9084,0.0,0.0005,0.4779,0.0,0.2487,0.0677,0.0,0.728,0.055,0.0,0.9976,0.4514,0.0,0.8098,0.8925,0.0,0.3371,0.9727,0.0,0.0142,0.6183,0.0,0.138,0.1552,0.0,0.5946,0.009,0.0,0.9642,0.3143,0.0,0.9071,0.7903,0.0,0.4757,0.9994,0.0,0.0666,0.7494,0.0,0.056,0.27,0.0,0.4536,0.0022,0.0,0.8939,0.192,0.0,0.972,0.665,0.0,0.6162,0.9863,0.0,0.1536,0.8605,0.0,0.0094,0.4033,0.0,0.3164,0.0349,0.0,0.7921,0.0942,0.0,0.9993,0.5265,0.0,0.7474,0.9345,0.0,0.2681,
		0.943,0.0,0.002,0.5442,0.0,0.1937,0.1048,0.0,0.6671,0.0287,0.0,0.9868,0.386,0.0,0.859,0.848,0.0,0.4011,0.9901,0.0,0.0341,0.6816,0.0,0.0955,0.2061,0.0,0.5288,0.0008,0.0,0.9356,0.2545,0.0,0.9419,0.7339,0.0,0.542,0.9982,0.0,0.1034,0.8045,0.0,0.0295,0.3308,0.0,0.3881,0.0127,0.0,0.8496,0.1426,0.0,0.9897,0.6011,0.0,0.6795,0.9667,0.0,0.2043,0.9032,0.0,0.001,0.469,0.0,0.2564,0.0633,0.0,0.7358,0.0591,0.0,0.9984,0.4602,0.0,0.8028,0.8979,0.0,0.3288,0.9698,0.0,0.0122,0.6097,0.0,0.1441,
		0.1488,0.0,0.6032,0.0108,0.0,0.9675,0.3225,0.0,0.9019,0.7975,0.0,0.4668,0.9989,0.0,0.0623,0.7416,0.0,0.0602,0.2622,0.0,0.4624,0.0014,0.0,0.8992,0.199,0.0,0.969,0.6733,0.0,0.6076,0.9883,0.0,0.1472,0.8543,0.0,0.0112,0.3946,0.0,0.3246,0.0318,0.0,0.7992,0.0994,0.0,0.9987,0.5354,0.0,0.7397,0.9388,0.0,0.2603,0.9388,0.0,0.0013,0.5354,0.0,0.2008,0.0994,0.0,0.6754,0.0318,0.0,0.9888,0.3946,0.0,0.8528,0.8543,0.0,0.3924,0.9883,0.0,0.031,0.6733,0.0,0.1008,0.199,0.0,0.5376,0.0014,0.0,
		0.9399,0.2622,0.0,0.9377,0.7417,0.0,0.5332,0.9989,0.0,0.0981,0.7975,0.0,0.0326,0.3225,0.0,0.3968,0.0108,0.0,0.8559,0.1488,0.0,0.9878,0.6097,0.0,0.6712,0.9698,0.0,0.1972,0.8979,0.0,0.0016,0.4602,0.0,0.2642,0.0591,0.0,0.7436,0.0634,0.0,0.999,0.4691,0.0,0.7957,0.9032,0.0,0.3205,0.9667,0.0,0.0103,0.6011,0.0,0.1504,0.1426,0.0,0.6119,0.0127,0.0,0.9705,0.3308,0.0,0.8966,0.8045,0.0,0.458,0.9982,0.0,0.0581,0.7339,0.0,0.0644,0.2545,0.0,0.4713,0.0008,0.0,0.9045,0.2061,0.0,0.9659,0.6816,
		0.0,0.5989,0.9901,0.0,0.141,0.848,0.0,0.0132,0.386,0.0,0.3329,0.0287,0.0,0.8063,0.1048,0.0,0.998,0.5442,0.0,0.7319,0.943,0.0,0.2526,0.9345,0.0,0.0007,0.5265,0.0,0.2079,0.0942,0.0,0.6837,0.035,0.0,0.9906,0.4033,0.0,0.8464,0.8605,0.0,0.3838,0.9863,0.0,0.028,0.665,0.0,0.1062,0.192,0.0,0.5464,0.0022,0.0,0.944,0.2701,0.0,0.9334,0.7494,0.0,0.5243,0.9994,0.0,0.0929,0.7903,0.0,0.0358,0.3143,0.0,0.4055,0.009,0.0,0.8621,0.1552,0.0,0.9858,0.6183,0.0,0.6629,0.9727,0.0,0.1902,0.8925,0.0,
		0.0024,0.4514,0.0,0.272,0.055,0.0,0.7513,0.0677,0.0,0.9995,0.4779,0.0,0.7885,0.9084,0.0,0.3122,0.9634,0.0,0.0086,0.5924,0.0,0.1568,0.1364,0.0,0.6205,0.0147,0.0,0.9734,0.3392,0.0,0.8911,0.8115,0.0,0.4492,0.9974,0.0,0.054,0.726,0.0,0.0688,0.2468,0.0,0.4801,0.0004,0.0,0.9097,0.2133,0.0,0.9626,0.6898,0.0,0.5902,0.9918,0.0,0.1349,0.8416,0.0,0.0153,0.3774,0.0,0.3413,0.0259,0.0,0.8132,0.1103,0.0,0.9972,0.553,0.0,0.724,0.947,0.0,0.2449,0.93,0.0,0.0003,0.5177,0.0,0.2151,0.0891,0.0,
		0.6919,0.0383,0.0,0.9922,0.412,0.0,0.84,0.8666,0.0,0.3752,0.9842,0.0,0.0252,0.6566,0.0,0.1117,0.185,0.0,0.5552,0.0031,0.0,0.948,0.278,0.0,0.9289,0.757,0.0,0.5155,0.9998,0.0,0.0878,0.783,0.0,0.0391,0.3061,0.0,0.4142,0.0074,0.0,0.8681,0.1616,0.0,0.9836,0.6269,0.0,0.6545,0.9755,0.0,0.1833,0.8869,0.0,0.0033,0.4426,0.0,0.2799,0.051,0.0,0.7589,0.0722,0.0,0.9998,0.4867,0.0,0.7812,0.9134,0.0,0.3041,0.96,0.0,0.007,0.5837,0.0,0.1633,0.1304,0.0,0.6291,0.0169,0.0,0.9762,0.3476,0.0,
		0.8855,0.8184,0.0,0.4404,0.9964,0.0,0.0501,0.7181,0.0,0.0734,0.2392,0.0,0.489,0.0001,0.0,0.9147,0.2206,0.0,0.9591,0.698,0.0,0.5815,0.9933,0.0,0.1289,0.8351,0.0,0.0175,0.3688,0.0,0.3497,0.0231,0.0,0.8201,0.1159,0.0,0.9962,0.5618,0.0,0.7161,0.9509,0.0,0.2373,0.9254,0.0,0.0001,0.5088,0.0,0.2225,0.0841,0.0,0.7,0.0417,0.0,0.9937,0.4207,0.0,0.8335,0.8726,0.0,0.3667,0.9819,0.0,0.0225,0.6482,0.0,0.1173,0.1782,0.0,0.564,0.0041,0.0,0.9519,0.2859,0.0,0.9243,0.7646,0.0,0.5066,1.0,0.0,
		0.0829,0.7757,0.0,0.0426,0.298,0.0,0.4229,0.006,0.0,0.874,0.1682,0.0,0.9813,0.6355,0.0,0.6461,0.9782,0.0,0.1765,0.8813,0.0,0.0044,0.4338,0.0,0.2879,0.0472,0.0,0.7664,0.0769,0.0,1.0,0.4956,0.0,0.7739,0.9183,0.0,0.2959,0.9565,0.0,0.0056,0.5749,0.0,0.1699,0.1245,0.0,0.6376,0.0193,0.0,0.9788,0.3561,0.0,0.8798,0.8252,0.0,0.4316,0.9953,0.0,0.0463,0.7101,0.0,0.0781,0.2317,0.0,0.4978,0.0,0.0,0.9195,0.228,0.0,0.9556,0.7061,0.0,0.5727,0.9947,0.0,0.123,0.8285,0.0,0.0199,0.3603,0.0,
		0.3582,0.0205,0.0,0.8268,0.1216,0.0,0.995,0.5706,0.0,0.7081,0.9547,0.0,0.2298,0.9207,0.0,0.0,0.5,0.0,0.2299,0.0793,0.0,0.7081,0.0454,0.0,0.995,0.4295,0.0,0.8268,0.8784,0.0
		};
	//build triangles to render circle
	unsigned int indices[] = {
		0,1,2,0,3,2,0,4,3,0,5,4,0,6,5,0,7,6,0,8,7,0,9,8,0,10,9,0,11,10,0,12,11,0,13,12,0,14,13,0,15,14,0,16,15,0,17,16,0,18,17,0,19,18,0,20,19,0,21,20,0,22,21,0,23,22,0,24,23,0,25,24,0,26,25,0,27,26,0,28,27,0,29,28,0,30,29,0,31,30,0,32,31,0,33,32,0,34,33,0,35,34,0,36,35,0,37,36,0,38,37,0,39,38,0,40,39,0,41,40,0,42,41,0,43,42,0,44,43,0,45,44,0,46,45,0,47,46,0,48,47,0,49,48,0,50,49,0,51,50,0,52,51,0,53,52,0,54,53,0,55,54,0,56,55,0,57,56,0,58,57,0,59,58,0,60,59,0,61,60,0,62,61,0,63,
		62,0,64,63,0,65,64,0,66,65,0,67,66,0,68,67,0,69,68,0,70,69,0,71,70,0,72,71,0,73,72,0,74,73,0,75,74,0,76,75,0,77,76,0,78,77,0,79,78,0,80,79,0,81,80,0,82,81,0,83,82,0,84,83,0,85,84,0,86,85,0,87,86,0,88,87,0,89,88,0,90,89,0,91,90,0,92,91,0,93,92,0,94,93,0,95,94,0,96,95,0,97,96,0,98,97,0,99,98,0,100,99,0,101,100,0,102,101,0,103,102,0,104,103,0,105,104,0,106,105,0,107,106,0,108,107,0,109,108,0,110,109,0,111,110,0,112,111,0,113,112,0,114,113,0,115,114,0,116,115,0,117,116,0,
		118,117,0,119,118,0,120,119,0,121,120,0,122,121,0,123,122,0,124,123,0,125,124,0,126,125,0,127,126,0,128,127,0,129,128,0,130,129,0,131,130,0,132,131,0,133,132,0,134,133,0,135,134,0,136,135,0,137,136,0,138,137,0,139,138,0,140,139,0,141,140,0,142,141,0,143,142,0,144,143,0,145,144,0,146,145,0,147,146,0,148,147,0,149,148,0,150,149,0,151,150,0,152,151,0,153,152,0,154,153,0,155,154,0,156,155,0,157,156,0,158,157,0,159,158,0,160,159,0,161,160,0,162,161,0,163,162,0,164,163,0,165,
		164,0,166,165,0,167,166,0,168,167,0,169,168,0,170,169,0,171,170,0,172,171,0,173,172,0,174,173,0,175,174,0,176,175,0,177,176,0,178,177,0,179,178,0,180,179,0,181,180,0,182,181,0,183,182,0,184,183,0,185,184,0,186,185,0,187,186,0,188,187,0,189,188,0,190,189,0,191,190,0,192,191,0,193,192,0,194,193,0,195,194,0,196,195,0,197,196,0,198,197,0,199,198,0,200,199,0,201,200,0,202,201,0,203,202,0,204,203,0,205,204,0,206,205,0,207,206,0,208,207,0,209,208,0,210,209,0,211,210,0,212,211,
		0,213,212,0,214,213,0,215,214,0,216,215,0,217,216,0,218,217,0,219,218,0,220,219,0,221,220,0,222,221,0,223,222,0,224,223,0,225,224,0,226,225,0,227,226,0,228,227,0,229,228,0,230,229,0,231,230,0,232,231,0,233,232,0,234,233,0,235,234,0,236,235,0,237,236,0,238,237,0,239,238,0,240,239,0,241,240,0,242,241,0,243,242,0,244,243,0,245,244,0,246,245,0,247,246,0,248,247,0,249,248,0,250,249,0,251,250,0,252,251,0,253,252,0,254,253,0,255,254,0,256,255,0,257,256,0,258,257,0,259,258,0,260,
		259,0,261,260,0,262,261,0,263,262,0,264,263,0,265,264,0,266,265,0,267,266,0,268,267,0,269,268,0,270,269,0,271,270,0,272,271,0,273,272,0,274,273,0,275,274,0,276,275,0,277,276,0,278,277,0,279,278,0,280,279,0,281,280,0,282,281,0,283,282,0,284,283,0,285,284,0,286,285,0,287,286,0,288,287,0,289,288,0,290,289,0,291,290,0,292,291,0,293,292,0,294,293,0,295,294,0,296,295,0,297,296,0,298,297,0,299,298,0,300,299,0,301,300,0,302,301,0,303,302,0,304,303,0,305,304,0,306,305,0,307,306,0,
		308,307,0,309,308,0,310,309,0,311,310,0,312,311,0,313,312,0,314,313,0,315,314,0,316,315,0,317,316,0,318,317,0,319,318,0,320,319,0,321,320,0,322,321,0,323,322,0,324,323,0,325,324,0,326,325,0,327,326,0,328,327,0,329,328,0,330,329,0,331,330,0,332,331,0,333,332,0,334,333,0,335,334,0,336,335,0,337,336,0,338,337,0,339,338,0,340,339,0,341,340,0,342,341,0,343,342,0,344,343,0,345,344,0,346,345,0,347,346,0,348,347,0,349,348,0,350,349,0,351,350,0,352,351,0,353,352,0,354,353,0,355,354,
		0,356,355,0,357,356,0,358,357,0,359,358,0,360,359,0,360,1
		};
	unsigned int VBO,VAO,EBO;
	//Prepare Buffers
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	//Bind Buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
	//Position attribute
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(w,h,1.0f));
	glUseProgram(shaderProgram);
	//Set Uniforms
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,1080,GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
	//Delete Buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void exstar::Camera::drawEllipse(exstar::Point pos, exstar::Dimension size){
	drawEllipse(pos.x,pos.y,size.width,size.height);
}
void exstar::Camera::drawEllipse(int x,int y, exstar::Dimension size){
	drawEllipse(x,y,size.width,size.height);
}
void exstar::Camera::drawEllipse(exstar::Point pos,int w,int h){
	drawEllipse(pos.x,pos.y,w,h);
}
//-----------------------------DRAW CIRCLE-----------------------------
void exstar::Camera::drawCircle(int x,int y,int r){

	drawEllipse(x,y,r*2,r*2);
}
void exstar::Camera::drawCircle(exstar::Point pos,int r){
	drawEllipse(pos.x,pos.y,r*2,r*2);
}
//-----------------------------DRAW SHAPE-----------------------------
void exstar::Camera::drawShape(exstar::ArrayList<exstar::Point>* shape,int x,int y,int w,int h){
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec2 aPos;\n"
									 "layout (location = 1) in vec3 aColor;\n"
									 "out VS_OUT {\n"
									 "    vec3 color;\n"
									 "} vs_out;\n"
									 "uniform mat4 ModelMatrix;\n"
									 "uniform mat4 projection;\n"
									 "void main()\n"
									 "{\n"
									 "    vs_out.color = aColor;\n"
									 "    gl_Position = projection*(ModelMatrix*vec4(aPos.x,aPos.y,0.0,1.0));\n"
									 "}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "in vec3 fColor;\n"
									   "void main()\n"
									   "{\n"
									   "    FragColor = vec4(fColor, 1.0);\n"
									   "}\0";
	//Create and Convert GeometryShaderSource to proper format
	std::string geometryShaderSourceRef = "#version 330 core\nlayout (points) in;\nlayout (triangle_strip, max_vertices = " +  std::to_string(shape->size) + ") out;\nin VS_OUT {\n\tvec3 color;\n} gs_in[];\nout vec3 fColor;\nvoid build_shape(vec4 position)\n{\n\tfColor = gs_in[0].color;\n";
	for(int i = 0; i<shape->size;i++){
		if(shape->get(i).x >w || shape->get(i).x < 0){
			throw exstar::exception("exstar::Camera::drawShape - x position is out of range 0-" + std::to_string(w));
		}else if(shape->get(i).y >h || shape->get(i).y < 0){
			throw exstar::exception("exstar::Camera::drawShape - y position is out of range 0-" + std::to_string(h));
		}
		geometryShaderSourceRef+="\tgl_Position = position + vec4("+std::to_string((((float)shape->get(i).x)/size->width*2))+","+std::to_string((((((float)shape->get(i).y)-h))/(-size->height)*2))+", 0.0,0.0);\n\tEmitVertex();\n";
	}
	geometryShaderSourceRef+="\tEndPrimitive();\n}\nvoid main() {\n\tbuild_shape(gl_in[0].gl_Position);\n}";
	const char* geometryShaderSource = geometryShaderSourceRef.c_str();
	unsigned int vertexShader,fragmentShader,geometryShader,shaderProgram;
	//Create and Compile VertexShader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
	glCompileShader(vertexShader);
	//Create and Compile FragmentShader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
	glCompileShader(fragmentShader);
	//Create and Compile GeometryShader
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShader,1,&geometryShaderSource,NULL);
	glCompileShader(geometryShader);
	//Create and Link ShaderProgram
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glAttachShader(shaderProgram,geometryShader);
	glLinkProgram(shaderProgram);
	//Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
	//Pass Camera's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);
	float points[] = {
    	0.0f,  0.0f, 0.0f, 1.0f, 0.0f, // top-right
		};  
	unsigned int VBO, VAO;
	//Prepare Buffers
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    //Bind Buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(points), &points, GL_STATIC_DRAW);
    //Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    //Color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(2*sizeof(float)));
    glBindVertexArray(0);
    //Transformations
	glm::mat4 projection;
	projection = glm::ortho((int)pos->x + 0.0f,(float)size->width + (int)pos->x,(float)size->height + (int)pos->y,0.0f + (int)pos->y,-1.0f,1.0f);
	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix,glm::vec3(x,y,0.0f));
	ModelMatrix = glm::scale(ModelMatrix,glm::vec3(w,h,1.0f));
    glUseProgram(shaderProgram);
    //Set Uniforms
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,glm::value_ptr(projection));
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS,0,1);
    glBindVertexArray(0);
    //Delete Buffers
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void exstar::Camera::drawShape(exstar::ArrayList<exstar::Point>* shape,exstar::Point pos,int w,int h){
	drawShape(shape,pos.x,pos.y,w,h);
}
void exstar::Camera::drawShape(exstar::ArrayList<exstar::Point>* shape,exstar::Point pos,exstar::Dimension size){
	drawShape(shape,pos.x,pos.y,size.width,size.height);
}
void exstar::Camera::drawShape(exstar::ArrayList<exstar::Point>* shape,int x,int y,exstar::Dimension size){
	drawShape(shape,x,y,size.width,size.height);
}
//-----------------------------DRAW LINE-----------------------------
void exstar::Camera::drawLine(int x1,int y1,int x2,int y2){
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec2 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x,aPos.y,0.0f,1.0f);\n"
									 "}\0";
	//Pass Camera's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);
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
		(float)(x1-pos->x)/size->width*2.0 -1.0,//x1
		-((float)(y1-pos->y)/size->height*2.0-1.0),//y1
		(float)(x2-pos->x)/size->width*2.0 -1.0,//x2
		-((float)(y2-pos->y)/size->height*2.0-1.0)//y2
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
}
void exstar::Camera::drawLine(exstar::Point pos1,exstar::Point pos2){
	drawLine(pos1.x,pos1.y,pos2.x,pos2.y);
}
void exstar::Camera::drawLine(exstar::Point pos1,exstar::Vector2d offset){
	drawLine(pos1.x,pos1.y,offset.getX(),offset.getY());
}
//-----------------------------DRAW PIXEL-----------------------------
void exstar::Camera::drawPixel(int x,int y){
	const char* vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec2 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x,aPos.y,0.0f,1.0f);\n"
									 "}\0";
	//Pass Camera's color
	float r,g,b,a;
	r = exstar::Color::getFloat(color->r);
	g = exstar::Color::getFloat(color->g);
	b = exstar::Color::getFloat(color->b);
	a = exstar::Color::getFloat(color->a);
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
		(float)(x-pos->x)/size->width*2.0 -1.0,//x
		-((float)((y-1)-pos->y)/size->height*2.0-1.0)//y
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
}
void exstar::Camera::drawPixel(exstar::Point pos){
	drawPixel(pos.x,pos.y);
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