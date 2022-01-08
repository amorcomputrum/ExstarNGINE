#include "Exstar/exstarglad/gl.h"

#include "Exstar/Utils/Exception.h"
#include "Exstar/Graphics/Shaders/GLSL.h"

exstar::GLSL::GLSL(const std::string shader,std::string id){
	this->id = id;
	CompileShaders(shader);
}
void exstar::GLSL::use(){
	glUseProgram(Program);
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
	if(vertexShaderSource == "THIS SHADER DOESN'T EXIST" || fragmentShaderSource == "THIS SHADER DOESN'T EXIST"){
		throw exstar::exception("exstar::GLSL::CompileShaders - SHADER NOT FOUND");
	}
	unsigned int vertexShader,fragmentShader,geometryShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader,1,&vertexShaderSource.c_str(),NULL);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader,1,&fragmentShaderSource.c_str(),NULL);

	Program = glCreateShader();
	glAttachShader(Program,vertexShader);
	glAttachShader(Program,fragmentShader);

	if(geometryShaderSource != "THIS SHADER DOESN'T EXIST"){
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

}