#include <Exstar/Window.h>

class Window : public exstar::Window
{
public:
	exstar::Sprite* sprite;
	Window(int width,int height,const char* title) : exstar::Window(width,height,title){
		sprite = new exstar::Sprite("index.jpg");
		std::cout << sprite->getWidth() << std::endl;
	}
	void render(exstar::Camera camera){
		// vertex shader
		unsigned int verexShader;
		verexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(verexShader,1,&vertexShaderSource,NULL);
		glCompileShader(verexShader);
		// fragment shader
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
		glCompileShader(fragmentShader);
		// link shaders
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram,verexShader);
		glAttachShader(shaderProgram,fragmentShader);
		glLinkProgram(shaderProgram);
		//clear cache
		glDeleteShader(verexShader);
		glDeleteShader(fragmentShader);
		// set up vertex data (and buffer(s)) and configure vertex attributes
		float verticies[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f};
		//get the buffer
		unsigned int VBO;
		unsigned int VAO;
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1,&VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER,sizeof(verticies),verticies,GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary
		glBindVertexArray(0);
		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0); 
		glm::mat4 projection;
		projection = glm::ortho(pos->x,0.0f,(float)size->width+pos->x,(float)size->height+pos->y,-1.0f,1.0);
		//tell how to process vertex data
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"ModelMatrix"),1,GL_FALSE,glm::value_ptr(ModelMatrix));
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);

		

		

		
		//set the verticies/shape
		
		glDrawArrays(GL_TRIANGLES,0,3);
		
	}
private:
	int r,b,a;
	const char *vertexShaderSource = "#version 330 core\n"
										"layout (location = 0) in vec3 aPos;\n"
										"uniform mat4 ModelMatrix\n"
										"uniform mat4 projection\n"
										"void main()\n"
										"{\n"
										" gl_Position = projection*(ModelMatrix*vec4(aPos.x, aPos.y, aPos.z, 1.0));\n"
										"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
										"out vec4 FragColor;\n"
										"void main()\n"
										"{\n"
										"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
										"}\0";
};