R"(

#VERTEX

#version 330 core
layout (location = 0) in vec2 Point;
uniform mat4 ModelMatrix;
uniform mat4 projection;
void main(){
	gl_Position = projection*(ModelMatrix*vec4(Point,1.0f,1.0f));
}

#FRAGMENT

#version 330 core
out vec4 FragColor;
uniform vec4 Color;
void main()
{
	FragColor = Color;
}
)"