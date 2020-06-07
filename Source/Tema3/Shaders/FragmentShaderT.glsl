#version 330
 
uniform sampler2D texture_1;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = texture2D(texture_1, texcoord);
	if (out_color.w <= 0.5f) {
		discard;
	}
}