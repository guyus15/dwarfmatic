#version 460 core

in vec3 normal;
in vec2 texCoords;
in vec3 fragPos;

out vec4 FragColour;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

uniform vec3 light_colour;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main()
{
    float ambient_strength = 0.2f;
    vec3 ambient = ambient_strength * light_colour;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - fragPos);
    vec3 view_dir = normalize(view_pos - fragPos);
    vec3 reflect_dir = reflect(-light_dir, norm);

    // Prevent dot product calculation from becoming negative.
    float diff = max(dot(norm, light_dir), 0.0f);
    vec3 diffuse = diff * light_colour;

    float specular_strength = 0.5;
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);
    vec3 specular = spec * specular_strength * light_colour;

    vec3 result = ambient + diffuse + specular;
    FragColour = vec4(result, 1.0f) * texture(texture_diffuse1, texCoords);
}