#include "resource_manager.h"
#include "utils/logging.h"

#include "stb/stb_image.h"

#include <fstream>
#include <iostream>
#include <sstream>

ResourceManager ResourceManager::s_instance;

Shader ResourceManager::LoadShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    Get().m_shaders[name] = LoadShaderFromFile(vertex_shader_path, fragment_shader_path);
    return Get().m_shaders[name];
}

Shader& ResourceManager::GetShader(const std::string& name)
{
    return Get().m_shaders[name];
}

Texture2D ResourceManager::LoadTexture(const std::string& name, const std::string& path, bool alpha, bool flip_on_load)
{
    Get().m_textures[name] = LoadTextureFromFile(path, alpha, flip_on_load);
    return Get().m_textures[name];
}

Texture2D ResourceManager::GetTexture(const std::string& name)
{
    return Get().m_textures[name];
}

Shader ResourceManager::LoadShaderFromFile(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    std::string vertex_code, fragment_code;
    std::ifstream vertex_shader_file, fragment_shader_file;

    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertex_shader_file.open(vertex_shader_path);
        fragment_shader_file.open(fragment_shader_path);

        std::stringstream vertex_shader_stream, fragment_shader_stream;

        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();

        vertex_shader_file.close();
        fragment_shader_file.close();

        vertex_code = vertex_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        DFM_CORE_ERROR("Failed to read shader file.");
    }

    Shader shader{};
    shader.Compile(vertex_code, fragment_code);

    return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const std::string& path, const bool alpha, const bool flip_on_load)
{
    Texture2D texture;

    if (alpha)
    {
        texture.EnableAlpha(true);
    }

    if (flip_on_load)
    {
        stbi_set_flip_vertically_on_load(flip_on_load);
    }

    int width, height, no_channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &no_channels, 0);

    texture.Generate(width, height, data);

    stbi_image_free(data);

    // Disable flipping vertically on load after texture has been loaded.
    stbi_set_flip_vertically_on_load(false);

    return texture;
}
