#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 UV;
layout (location = 3) in uint material;

out vec2 UVs;
out vec3 worldPos;
out vec3 norm;
flat out uint materialnum;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 offsets[7] = vec3[](vec3(1, 1, 1), vec3(-10, 10, -10), vec3(15, -16, 18), vec3(21, 19, -15), vec3(10, 19, 19), vec3(-20, 20, -20), vec3(-16, -16, -16));

void main()
{
	vec3 pos = vec3(model * vec4(position, 1.0f));
	pos += 100*offsets[gl_InstanceID];
	
	gl_Position = projection * view * vec4(pos, 1.0f);
	
	UVs = UV;
	worldPos = pos;
	norm = normal;
	materialnum = material;
}
