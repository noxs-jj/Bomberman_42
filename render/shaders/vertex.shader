#version 400

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in float in_text;

uniform float keyframe;
uniform float leg_pos;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2			uv;
flat out float		text;

vec4 anim_pos;
float test = 1;




mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s,
		oc * axis.z * axis.x + axis.y * s,  0.0, oc * axis.x * axis.y + axis.z * s,
		oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s,  0.0, oc * axis.z * axis.x - axis.y * s,
		oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,0.0, 0.0, 0.0, 0.0, 1.0);
}

void handle_anim()
{
	float rot = keyframe;
	vec3 right = vec3(1, 0, 0);
	if (keyframe == 0)
		return ;
	if (in_Position.y < leg_pos)
	{
		if (keyframe > 1)
			rot = 1 - (keyframe - 1);
		if (keyframe > 3)
			rot = (keyframe - 4);
		anim_pos.y -= leg_pos;
		if (in_Position.x > 0)
			anim_pos *= rotationMatrix(right, -rot);
		else
			anim_pos *= rotationMatrix(right, rot);
		anim_pos.y += leg_pos;
	}
}

void main(void)
{

	anim_pos.xyz = in_Position.xyz;
	anim_pos.w = 1;
	handle_anim();
	uv = in_uv;
	text = in_text;
	//text = 1;
    gl_Position = vec4(anim_pos.x, anim_pos.y, anim_pos.z, test);
    gl_Position *= M;
    gl_Position *= V;
    gl_Position *= P;
}
