#version 460 core

in vec3 normal;
in vec2 texCoords;
in vec3 fragPos;

out vec4 FragColour;

struct DirectionalLight
{
    vec4 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight
{
    vec4 position;

    float constant;
    float linear;
    float quadratic;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};
#define MAX_NO_POINT_LIGHTS 128

layout (std140) uniform Lighting
{
    vec4 viewPos;
    int pointLightsSize;
    PointLight pointLights[MAX_NO_POINT_LIGHTS];
    DirectionalLight directionalLight;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(vec3(viewPos.x, viewPos.y, viewPos.z) - fragPos);

    // Directional lights
    vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDir);

    // Point lights
    for (int i = 0; i < pointLightsSize; i++)
    {
        result += CalculatePointLight(pointLights[i], norm, fragPos, viewDir);
    }

    FragColour = vec4(result, 1.0f);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.direction));

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0f), 32);

    // Combine results
    vec3 ambient = vec3(light.ambient) * vec3(texture(texture_diffuse1, texCoords));
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(texture_diffuse1, texCoords));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(texture_specular1, texCoords));

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(vec3(light.position) - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0f);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);

    // Attentuation
    float distance = length(vec3(light.position) - fragPos);
    float attentuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine results
    vec3 ambient = vec3(light.ambient) * vec3(texture(texture_diffuse1, texCoords));
    vec3 diffuse = vec3(light.diffuse) * diff * vec3(texture(texture_diffuse1, texCoords));
    vec3 specular = vec3(light.specular) * spec * vec3(texture(texture_specular1, texCoords));

    ambient *= attentuation;
    diffuse *= attentuation;
    specular *= attentuation;

    return (ambient + diffuse + specular);
}