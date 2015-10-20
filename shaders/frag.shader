#version 400

in vec2 uv;
in float text;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;

out vec4 FragColor;

void wich_one()
{
	vec2 t = uv;
	if (text == 0)
		FragColor = (vec4(texture(texture0, t).r, texture(texture0, t).g, texture(texture0, t).b, 1));
	if (text == 1)
		FragColor = (vec4(texture(texture1, t).r, texture(texture1, t).g, texture(texture1, t).b, 1));
	if (text == 2)
		FragColor = (vec4(texture(texture2, t).r, texture(texture2, t).g, texture(texture2, t).b, 1));
	if (text == 3)
		FragColor = (vec4(texture(texture3, t).r, texture(texture3, t).g, texture(texture3, t).b, 1));
	if (text == 4)
		FragColor = (vec4(texture(texture4, t).r, texture(texture4, t).g, texture(texture4, t).b, 1));
	if (text == 5)
		FragColor = (vec4(texture(texture5, t).r, texture(texture5, t).g, texture(texture5, t).b, 1));
}

void main(void)
{
	FragColor = vec4(1, 1, 1, 1);
	wich_one();
}