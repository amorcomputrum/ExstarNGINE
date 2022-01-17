#include <vector>

#include "Exstar/exstarglad/gl.h"

#include "Exstar/Utils/Exception.h"

#include "Exstar/Graphics/Shaders/GLSL.h"

exstar::GLSL::GLSL(){}

exstar::GLSL::GLSL(const std::string SHADER){
	CompileShaders(SHADER);
}

void exstar::GLSL::use(){
	glUseProgram(Program);
}

void exstar::GLSL::uniformMat4(const char* uniform, glm::mat4& matrix){
	glUniformMatrix4fv(glGetUniformLocation(Program, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void exstar::GLSL::uniformVec4(const char* uniform, glm::vec4& vector){
	glUniform4fv(glGetUniformLocation(Program, uniform), 1, glm::value_ptr(vector));
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

void exstar::GLSL::CompileShaders(const std::string SHADER){
	std::string vertexShaderSourceReference   = loadShader(SHADER,exstar::GLSL::Shader::VERTEX  );
	std::string fragmentShaderSourceReference = loadShader(SHADER,exstar::GLSL::Shader::FRAGMENT);
	std::string geometryShaderSourceReference = loadShader(SHADER,exstar::GLSL::Shader::GEOMETRY);

	if(vertexShaderSourceReference == "THIS SHADER DOESN'T EXIST" || fragmentShaderSourceReference == "THIS SHADER DOESN'T EXIST"){
		throw exstar::exception("exstar::GLSL::CompileShaders - SHADER NOT FOUND");
	}

	const char* VERTEX_SHADER_SOURCE   = vertexShaderSourceReference.c_str(  );
	const char* FRAGMENT_SHADER_SOURCE = fragmentShaderSourceReference.c_str();
	const char* GEOMETRY_SHADER_SOURCE = geometryShaderSourceReference.c_str();

	unsigned int vertexShader,fragmentShader,geometryShader;

	vertexShader   = glCreateShader(GL_VERTEX_SHADER  );
	glShaderSource(vertexShader,   1, &VERTEX_SHADER_SOURCE,   NULL);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, NULL);

	Program = glCreateProgram();
	glAttachShader(Program, vertexShader  );
	glAttachShader(Program, fragmentShader);

	if(geometryShaderSourceReference != "THIS SHADER DOESN'T EXIST"){
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &GEOMETRY_SHADER_SOURCE, NULL);
		glAttachShader(Program, geometryShader);
	}

	glLinkProgram(Program);

	glDeleteShader(vertexShader  );
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);

}

std::string exstar::GLSL::loadShader(const std::string FILE, exstar::GLSL::Shader type){
	if(type == exstar::GLSL::Shader::VERTEX  ){
	        if(FILE.find("#VERTEX"  ) == std::string::npos) return "THIS SHADER DOESN'T EXIST";
	        std::string shader = "";
	        bool foundBegining = false;
	        for(int i = FILE.find("#VERTEX"  ) + 6; i < FILE.length(); i++){
	                if(!foundBegining){
	                        if(FILE[i] == '#') foundBegining = true;
	                }
	                if(i == FILE.find("#FRAGMENT") || i == FILE.find("#GEOMETRY")) break;
	                if(foundBegining) shader += FILE[i];
	        }
	        return shader;
	}
	 
	if(type == exstar::GLSL::Shader::FRAGMENT){
	        if(FILE.find("#FRAGMENT") == std::string::npos) return "THIS SHADER DOESN'T EXIST";
	        std::string shader = "";   
	        bool foundBegining = false;
	        for(int i = FILE.find("#FRAGMENT") + 7; i < FILE.length(); i++){
	                if(!foundBegining){
	                        if(FILE[i] == '#') foundBegining = true;
	                }
	                if(i == FILE.find("#VERTEX"  ) || i == FILE.find("#GEOMETRY")) break;
	                if(foundBegining) shader += FILE[i];
	        }
	        return shader;
	}
	 
	if(type == exstar::GLSL::Shader::GEOMETRY){
	        if(FILE.find("#GEOMETRY") == std::string::npos) return "THIS SHADER DOESN'T EXIST";
	        std::string shader = "";
	        bool foundBegining = false;
	        for(int i = FILE.find("#GEOMETRY") + 7; i < FILE.length(); i++){
	                if(!foundBegining){
	                        if(FILE[i] == '#') foundBegining = true;
	                }
	                if(i == FILE.find("#FRAGMENT") || i == FILE.find("#VERTEX")) break;
	                if(foundBegining) shader += FILE[i];
	        }
	        return shader;
	 
	}
	
	return "THIS SHADER DOESN'T EXIST";
}
