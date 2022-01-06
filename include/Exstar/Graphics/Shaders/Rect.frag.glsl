#version 330 core
out vec4 FragColor;
in vec4 bColor;
void main()
{
	FragColor = bColor;
}