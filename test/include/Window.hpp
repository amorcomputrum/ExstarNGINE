#include <Exstar/Window.h>

class Window : public exstar::Window
{
public:
	Window(int width,int height,const char* title) : exstar::Window(width,height,title){
	}
	void render(exstar::Camera camera){
		float verticies[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f};

		unsigned int VBO;
		glGenBuffers(1,&VBO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);

		unsigned int verexShader;
		verexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(verexShader,1,&vertexShaderSource,NULL);
		glCompileShader(verexShader);
		glBufferData(GL_ARRAY_BUFFER,sizeof(verticies),verticies,GL_STATIC_DRAW);
	}
private:
	
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
};