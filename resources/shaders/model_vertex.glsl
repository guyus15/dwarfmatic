#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

layout (std140) uniform Matrices
{
    mat4 view;
    mat4 projection;
};
uniform mat4 model;

out vec3 normal;
out vec2 texCoords;
out vec3 fragPos;

void main()
{
    normal = mat3(transpose(inverse(model))) * aNormal;
    texCoords = aTexCoords;
    fragPos = vec3(model * vec4(aPos, 1.0f));
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}