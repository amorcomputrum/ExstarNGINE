R"(

#VERTEX

#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 ModelMatrix;
uniform mat4 projection;
void main()
{
	gl_Position = projection*(ModelMatrix*vec4(aPos,1.0f));
}

#FRAGMENT

#version 330 core
uniform vec4 Color;
void main()
{
	gl_FragColor = Color;
}
)"