#version 330 core

uniform vec3 bg_color;

out vec4 color;

void main()
{
	color = vec4(bg_color, 1.0f);
}
