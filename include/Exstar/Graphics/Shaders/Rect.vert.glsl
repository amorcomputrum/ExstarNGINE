#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 bColor;
uniform mat4 ModelMatrix;
uniform mat4 projection;
uniform vec4 aColor;
void main()
{
	gl_Position = projection*(ModelMatrix*vec4(aPos,1.0f));
	bColor = aColor;
}