#version 330

layout(location=0) in vec3 my_coord;
layout(location=1) in vec3 my_normal;
layout(location=2) in vec2 my_TextCoord;
layout(location=3) in vec3 my_color;

uniform float speed;
uniform float waves;
uniform float depth;
uniform float time;

out vec3 culoare;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	culoare = my_color;

	gl_Position = Projection * View * Model * 
		vec4(my_coord.x,
			my_coord.y + sin((time * speed +  my_coord.x * waves) * 6.28) / depth, 
			my_coord.z, 
			1.0);

	if(sin((time * speed +  my_coord.x * waves) * 6.28) > 0.5) culoare = vec3(1);
	else culoare = vec3(0.2, 0.2, 1);
}