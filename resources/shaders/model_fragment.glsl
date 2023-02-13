#version 460 core

in vec3 normal;
in vec2 texCoords;

out vec4 FragColour;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

void main()
{
    FragColour = texture(texture_diffuse1, texCoords);
}