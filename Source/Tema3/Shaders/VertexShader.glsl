#version 330

layout(location=0) in vec3 my_coord;
layout(location=2) in vec3 my_normal;
layout(location=2) in vec2 my_TextCoord;
layout(location=3) in vec3 my_color;

out vec3 culoare;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float r;
uniform float g;
uniform float b;

void main()
{
	culoare = vec3(r, g, b);
	gl_Position = Projection * View * Model * vec4(my_coord, 1.0);
}
