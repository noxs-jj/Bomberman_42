#version 400

in vec2 uv;
flat in float text;

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

	t.y = 1.0f - uv.y;
	float toxt = text;
	if (toxt == 0)
		FragColor = (vec4(texture(texture0, t).r, texture(texture0, t).g, texture(texture0, t).b,
		texture(texture0, t).a));
	else if (toxt == 1)
		FragColor = (vec4(texture(texture1, t).r, texture(texture1, t).g, texture(texture1, t).b,
			texture(texture1, t).a));
	else if (toxt == 2)
		FragColor = (vec4(texture(texture2, t).r, texture(texture2, t).g, texture(texture2, t).b,
			texture(texture2, t).a));
	else if (toxt == 3)
		FragColor = (vec4(texture(texture3, t).r, texture(texture3, t).g, texture(texture3, t).b,
			texture(texture3, t).a));
	else if (toxt == 4)
		FragColor = (vec4(texture(texture4, t).r, texture(texture4, t).g, texture(texture4, t).b,
			texture(texture4, t).a));
	else if (toxt == 5)
		FragColor = (vec4(texture(texture5, t).r, texture(texture5, t).g, texture(texture5, t).b,
			texture(texture5, t).a));
}

void main(void)
{
vec2 t = uv;
	FragColor = vec4(1, 1, 1, 1);
	wich_one();
//FragColor = (vec4(texture(texture0, t).r, texture(texture0, t).g, texture(texture1, t).b, 1));
}
