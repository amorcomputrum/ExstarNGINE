#ifndef EXSTAR_GRAPHICS_SHADERS_GLSL_H
#define EXSTAR_GRAPHICS_SHADERS_GLSL_H

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
		GLSL(const std::string shader);
		void use();
		void uniformMat4(const char* uniform,glm::mat4& matrix);
		void uniformVec4(const char* uniform,glm::vec4& vector);
		unsigned int* getProgram();
		unsigned int* getVAO();
		unsigned int* getVBO();
		unsigned int* getEBO();
	private:
		unsigned int VBO,VAO,EBO,Program;
		void CompileShaders(const std::string shader);
		std::string loadShader(const std::string file,exstar::GLSL::Shader type);
	};
}
#endif