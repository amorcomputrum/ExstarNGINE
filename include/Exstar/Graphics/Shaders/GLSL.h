#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace exstar{
	class GLSL{
	public:
		enum Shader{
			VERTEX,FRAGMENT,GEOMETRY
		};
		GLSL();
		GLSL(const std::string SHADER);
		void use();
		void uniformMat4(const char* uniform, glm::mat4& matrix);
		void uniformVec4(const char* uniform, glm::vec4& vector);
		unsigned int* getProgram();
		unsigned int* getVAO();
		unsigned int* getVBO();
		unsigned int* getEBO();
	private:
		unsigned int VBO,VAO,EBO,Program;
		void CompileShaders(const std::string SHADER);
		std::string loadShader(const std::string FILE, exstar::GLSL::Shader type);
	};
}
