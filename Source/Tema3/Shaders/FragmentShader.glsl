#version 330

in vec3 culoare;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(culoare, 1);
}