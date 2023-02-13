#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "rendering/shader.h"
#include "rendering/texture2d.h"

#include <unordered_map>

class ResourceManager
{
public:
    static Shader LoadShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    static Shader& GetShader(const std::string& name);
    static Texture2D LoadTexture(const std::string& name, const std::string& path, bool alpha, bool flip_on_load = false);
    static Texture2D GetTexture(const std::string& name);

private:
    ResourceManager() = default;

    static Shader LoadShaderFromFile(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    static Texture2D LoadTextureFromFile(const std::string& path, bool alpha, bool flip_on_load);

    static ResourceManager& Get() { return s_instance; }
    static ResourceManager s_instance;

    std::unordered_map<std::string, Shader> m_shaders;
    std::unordered_map<std::string, Texture2D> m_textures;
};

#endif // RESOURCE_MANAGER_H