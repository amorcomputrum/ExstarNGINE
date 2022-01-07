#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/Shaders/GLSL.h"

exstar::GLSL::GLSL(const std::string shader,std::string id){
	this->id = id;
	CompileShaders(shader);
}
void exstar::GLSL::uniformMat4(const char* uniform,glm::mat4& matrix){
	glUniformMatrix4fv(glGetUniformLocation(Program,uniform),1,GL_FALSE,glm::value_ptr(*matrix));
}
void exstar::GLSL::uniformVec4(const char* uniform,glm::vec4& vector){
	glUniformMatrix4fv(glGetUniformLocation(Program,uniform),1,GL_FALSE,glm::value_ptr(*vector));
}
unsigned int* exstar::GLSL::getProgram(){
	return &Program;
}
unsigned int* exstar::GLSL::getVAO(){
	return &VAO;
}
unsigned int* exstar::GLSL::getVBO(){
	return &VBO;
}
unsigned int* exstar::GLSL::getEBO(){
	return &EBO;
}
void exstar::GLSL::CompileShaders(const std::string shader){
	std::string vertexShaderSource = loadShader(shader,exstar::GLSL::Shader::VERTEX);
	std::string fragmentShaderSource = loadShader(shader,exstar::GLSL::Shader::Fragment);
	std::string geometryShaderSource = loadShader(shader,exstar::GLSL::Shader::GEOMETRY);

	unsigned int vertexShader,fragmentShader,geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource.c_str(),NULL);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource.c_str(),NULL);

	Program = glCreateShader();
	glAttachShader(Program,vertexShader);
	glAttachShader(Program,fragmentShader);

	if(geometryShaderSource != "Doesn't exist"){
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader,1,&geometryShaderSource.c_str(),NULL);
		glAttachShader(Program,geometryShader);
	}

	glLinkProgram(Program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);

}
std::string loadShader(const std::string file,exstar::GLSL::Shader type){
	
}