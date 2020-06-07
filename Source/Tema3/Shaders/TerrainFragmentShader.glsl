#version 330

uniform sampler2D texture;
 
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 light_direction1;
uniform vec3 light_position1;
uniform vec3 eye_position;

uniform float cutoff;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

in vec3 culoare;
in vec2 texcoord;
in vec3 world_normal;
in vec3 world_position;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 L = normalize(light_position - world_position);
	vec3 N = normalize(world_normal);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	float ambient_light = 0.1;
	float result = ambient_light;

	float diffuse_light = material_kd * max(dot(L, N), 0);

	float specular_light = 0;
	if(diffuse_light > 0) specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);

	if(cos(cutoff) < dot(-L, light_direction))
	{
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cutoff);

		float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
		float light_att_factor = pow(linear_att, 2);
		float fa = 1 + length(world_position - light_position) + length(world_position - light_position) * length(world_position - light_position);
		result += (diffuse_light + specular_light) / fa * light_att_factor;
	}

	L = normalize(light_position1 - world_position);
	H = normalize(L + V);

	diffuse_light = material_kd * max(dot(L, N), 0);

	specular_light = 0;
	if(diffuse_light > 0) specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);

	if(cos(cutoff) < dot(-L, light_direction1))
	{
		float spot_light = dot(-L, light_direction1);
		float spot_light_limit = cos(cutoff);

		float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
		float light_att_factor = pow(linear_att, 2);
		float fa = 1 + length(world_position - light_position1) + length(world_position - light_position1) * length(world_position - light_position);
		result += (diffuse_light + specular_light) / fa * light_att_factor;
	}

	vec4 object_color = texture2D(texture, texcoord);
	out_color = vec4(result * vec3(object_color), 1);
}