#version 330 core

in vec2 UVs;
in vec3 worldPos;
in vec3 norm;
flat in uint materialnum;

out vec4 color;

uniform mat3 normMat;

uniform vec3 camPos;
uniform float shininess;

struct pointLight
{
	float ambient;
	float diffuse;
	float specular;
	
	vec3 color;
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
};

struct dirLight
{
	float ambient;
	float diffuse;
	float specular;
	
	vec3 color;
	vec3 direction;
};

struct Material
{                          // base alignement  // aligned offset
	vec3 ambient;          // 16               // 0
	vec3 diffuse;          // 16               // 16
	vec3 specular;         // 16               // 32
	
	float shiny;           // 4                // 48
};

const int MATERIAL_ARRAY_SIZE = 90;
//layout (std140) uniform materialBlock {
	//Material materials[MATERIAL_ARRAY_SIZE];
//};

uniform vec3 materials_ambient[MATERIAL_ARRAY_SIZE];
uniform vec3 materials_diffuse[MATERIAL_ARRAY_SIZE];
uniform vec3 materials_specular[MATERIAL_ARRAY_SIZE];
uniform float materials_shiny[MATERIAL_ARRAY_SIZE];

uniform sampler2D amb_texs[MATERIAL_ARRAY_SIZE];
uniform sampler2D diff_texs[MATERIAL_ARRAY_SIZE];
uniform sampler2D spec_texs[MATERIAL_ARRAY_SIZE];
uniform sampler2D bump_texs[MATERIAL_ARRAY_SIZE];

vec3 calculatePointLight(pointLight light, vec3 normal);
vec3 calculateDirLight(dirLight light, vec3 normal);

pointLight plight1 = pointLight(1.0f, 1.0f, 1.0f, vec3(1.0f, 1.0, 1.0f), vec3(10.0f, 10.0f, 10.0f), 0.1f, 0.1f, 0.001f);
pointLight plight2 = pointLight(1.0f, 1.0f, 1.0f, vec3(1.0f, 1.0, 1.0f), vec3(-10.0f, 10.0f, -10.0f), 0.1f, 0.1f, 0.001f);
pointLight plight3 = pointLight(1.0f, 1.0f, 1.0f, vec3(1.0f, 1.0, 1.0f), vec3(-10.0f, 10.0f, 10.0f), 0.1f, 0.1f, 0.001f);
pointLight plight4 = pointLight(1.0f, 1.0f, 1.0f, vec3(1.0f, 1.0, 1.0f), vec3(10.0f, 10.0f, -10.0f), 0.1f, 0.1f, 0.001f);

dirLight dlight1 = dirLight(1.0f, 0.9f, 0.0f, vec3(2.0f, 2.0f, 2.0f), vec3(-1.0f, -1.0f, 1.0f));

void main()
{
	vec3 normal = normalize(normMat * norm);
	
	/*vec4 fragcolor = vec4(1.0f, 1.0f, 1.0f, 1.0f); vec4(0.828125f, 0.68359375f, 0.21484375f, 1.0f); texture(materials[materialnum].tex, vec2(1.0f - UVs.x, 1.0f - UVs.y));
	if(fragcolor.a < 0.1f) {
		//discard;
	}*/
	
	color = /*vec4(calculatePointLight(plight1, normal) + 
				 calculatePointLight(plight2, normal) + 
				 calculatePointLight(plight3, normal) + 
				 calculatePointLight(plight4, normal), 
	1.0f) */  vec4(calculateDirLight(dlight1, normal), 1.0f);
}

vec3 calculatePointLight(pointLight light, vec3 normal)
{
	vec3 viewDir = normalize(camPos - worldPos);
	vec3 lightDir = normalize(light.position - worldPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	
	vec3 ambient = light.ambient * 
				   materials_ambient[materialnum] * 
				   light.color * 
				   vec3(texture(diff_texs[materialnum], vec2(1.0f - UVs.x, 1.0f - UVs.y)));
    vec3 diffuse = light.diffuse * 
				   materials_diffuse[materialnum] * 
				   max(dot(normal, lightDir), 0.0f) * 
				   light.color * 
				   vec3(texture(diff_texs[materialnum], vec2(1.0f - UVs.x, 1.0f - UVs.y)));
	vec3 specular = light.specular * 
					materials_specular[materialnum] * 
					pow(max(dot(normal, halfwayDir), 0.0f), materials_shiny[materialnum]) * 
					light.color *
					vec3(texture(diff_texs[materialnum], vec2(1.0f - UVs.x, 1.0f - UVs.y)));
	
	float distance = length(light.position - worldPos);
    float attenuation = min(1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance), 1.0f);
	
	return attenuation * (ambient + diffuse + specular);
}

vec3 calculateDirLight(dirLight light, vec3 normal)
{
	vec3 viewDir = normalize(camPos - worldPos);
	vec3 lightDir = normalize(-light.direction);
	vec3 halfwayDir = normalize(lightDir + viewDir);
        
    vec3 ambient = light.ambient * 
				   materials_ambient[materialnum] * 
				   light.color * 
				   vec3(texture(diff_texs[materialnum], vec2(1.0f - UVs.x, 1.0f - UVs.y)));
    vec3 diffuse = light.diffuse * 
				   materials_diffuse[materialnum] * 
				   max(dot(normal, lightDir), 0.0f) * 
				   light.color * 
				   vec3(texture(diff_texs[materialnum], vec2(1.0f - UVs.x, 1.0f - UVs.y)));
	vec3 specular = light.specular * 
					materials_specular[materialnum] * 
					pow(max(dot(normal, halfwayDir), 0.0f), materials_shiny[materialnum]) * 
					light.color * 
					vec3(texture(diff_texs[materialnum], vec2(1.0f - UVs.x, 1.0f - UVs.y)));
	
	return ((ambient + diffuse + specular) * light.color);
}
