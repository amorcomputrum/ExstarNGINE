#include <vector>

#include "Exstar/exstarglad/gl.h"

#include "Exstar/Utils/Exception.h"
#include "Exstar/Graphics/Shaders/GLSL.h"

exstar::GLSL::GLSL(){}

exstar::GLSL::GLSL(const std::string shader){
	CompileShaders(shader);
}
void exstar::GLSL::use(){
	glUseProgram(Program);
}
void exstar::GLSL::uniformMat4(const char* uniform,glm::mat4& matrix){
	glUniformMatrix4fv(glGetUniformLocation(Program,uniform),1,GL_FALSE,glm::value_ptr(matrix));
}
void exstar::GLSL::uniformVec4(const char* uniform,glm::vec4& vector){
	glUniform4fv(glGetUniformLocation(Program,uniform),1,glm::value_ptr(vector));
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
	std::string vertexShaderSourceReference = loadShader(shader,exstar::GLSL::Shader::VERTEX);
	std::string fragmentShaderSourceReference = loadShader(shader,exstar::GLSL::Shader::FRAGMENT);
	std::string geometryShaderSourceReference = loadShader(shader,exstar::GLSL::Shader::GEOMETRY);
	if(vertexShaderSourceReference == "THIS SHADER DOESN'T EXIST" || fragmentShaderSourceReference == "THIS SHADER DOESN'T EXIST"){
		throw exstar::exception("exstar::GLSL::CompileShaders - SHADER NOT FOUND");
	}
	const char* vertexShaderSource = vertexShaderSourceReference.c_str();
	const char* fragmentShaderSource = fragmentShaderSourceReference.c_str();
	const char* geometryShaderSource = geometryShaderSourceReference.c_str();

	unsigned int vertexShader,fragmentShader,geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);

	Program = glCreateProgram();
	glAttachShader(Program,vertexShader);
	glAttachShader(Program,fragmentShader);

	if(geometryShaderSourceReference != "THIS SHADER DOESN'T EXIST"){
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader,1,&geometryShaderSource,NULL);
		glAttachShader(Program,geometryShader);
	}

	glLinkProgram(Program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);

}
std::string exstar::GLSL::loadShader(const std::string file,exstar::GLSL::Shader type){
	if(type == exstar::GLSL::Shader::VERTEX){
	        if(file.find("#VERTEX") == std::string::npos) return "THIS SHADER DOESN'T EXIST";
	        std::string shader = "";
	        bool foundBegining = false;
	        for(int i = file.find("#VERTEX")+6; i < file.length();i++){
	                if(!foundBegining){
	                        if(file[i] == '#') foundBegining = true;
	                }
	                if(i == file.find("#FRAGMENT") || i == file.find("#GEOMETRY")) break;
	                if(foundBegining) shader += file[i];
	        }
	        return shader;
	}
	 
	if(type == exstar::GLSL::Shader::FRAGMENT){
	        if(file.find("#FRAGMENT") == std::string::npos) return "THIS SHADER DOESN'T EXIST";
	        std::string shader = "";   
	        bool foundBegining = false;
	        for(int i = file.find("#FRAGMENT")+7; i < file.length();i++){
	                if(!foundBegining){
	                        if(file[i] == '#') foundBegining = true;
	                }
	                if(i == file.find("#VERTEX") || i == file.find("#GEOMETRY")) break;
	                if(foundBegining) shader += file[i];
	        }
	        return shader;
	}
	 
	if(type == exstar::GLSL::Shader::GEOMETRY){
	        if(file.find("#GEOMETRY") == std::string::npos) return "THIS SHADER DOESN'T EXIST";
	        std::string shader = "";
	        bool foundBegining = false;
	        for(int i = file.find("#GEOMETRY")+7; i < file.length();i++){
	                if(!foundBegining){
	                        if(file[i] == '#') foundBegining = true;
	                }
	                if(i == file.find("#FRAGMENT") || i == file.find("#VERTEX")) break;
	                if(foundBegining) shader += file[i];
	        }
	        return shader;
	 
	}
	return "THIS SHADER DOESN'T EXIST";
}