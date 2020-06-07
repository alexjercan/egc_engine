#version 330

layout(location=0) in vec3 v_position;
layout(location=1) in vec3 v_normal;
layout(location=2) in vec2 v_texture_coord;
layout(location=3) in vec3 v_color;

uniform sampler2D heightmap;
uniform float  hmapWidth;
uniform float  hmapHeight;

out vec2 texcoord;
out vec3 culoare;
out vec3 world_normal;
out vec3 world_position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	float f = 10;
	texcoord = v_texture_coord;
	culoare = v_color;

	float height = texture2D(heightmap, v_texture_coord).r / f;
	vec2 texelSize = vec2(1.0 / hmapWidth, 1.0 / hmapHeight);
	float heightRight = texture2D(heightmap, vec2(v_texture_coord.x + texelSize.x, v_texture_coord.y)).r / f;
	float heightUp = texture2D(heightmap, vec2(v_texture_coord.x, v_texture_coord.y + texelSize.y)).r / f;

	float Hx = height - heightRight;
	float Hz = height - heightUp;

	vec3 normal = normalize(vec3(Hx, 1, Hz));
	world_normal = normalize(vec3(Model * vec4(normal, 1.0)));

	world_position = vec3(Model * vec4(v_position.x, height, v_position.z, 1.0));
	gl_Position = Projection * View * Model * vec4(v_position.x, height, v_position.z, 1.0);
}