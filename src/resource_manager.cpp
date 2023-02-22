/**
 * \file resource_manager.cpp
 */

#include "resource_manager.h"
#include "utils/logging.h"
#include "utils/profiling.h"

#include "stb/stb_image.h"

#include <fstream>
#include <iostream>
#include <sstream>

ResourceManager ResourceManager::s_instance;

/**
 * \brief Loads and gets a \code Shader at a particular path.
 * \param name The name used to identify the shader.
 * \param vertex_shader_path The path to the vertex shader code.
 * \param fragment_shader_path The path to the fragment shader code.
 * \return The loaded shader.
 */
Shader ResourceManager::LoadShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    DFM_PROFILE_FUNCTION();

    Get().m_shaders[name] = LoadShaderFromFile(vertex_shader_path, fragment_shader_path);
    return Get().m_shaders[name];
}

/**
 * \brief Gets a shader with the specified name.
 * \param name The name used to identify the shader.
 * \return The retrieved shader.
 */
Shader& ResourceManager::GetShader(const std::string& name)
{
    DFM_PROFILE_FUNCTION();
    return Get().m_shaders[name];
}

/**
 * \brief Loads and gets a \code Texture2D at a particular path.
 * \param name The name used to identify the texture.
 * \param path The path to the texture.
 * \param alpha Determines if the texture has an alpha channel.
 * \param flip_on_load Determines if the texture should be flipped vertically upon load.
 * \return The loaded texture.
 */
Texture2D ResourceManager::LoadTexture(const std::string& name, const std::string& path, bool alpha, bool flip_on_load)
{
    DFM_PROFILE_FUNCTION();

    Get().m_textures[name] = LoadTextureFromFile(path, alpha, flip_on_load);
    return Get().m_textures[name];
}

/**
 * \brief Gets a texture with the specified name.
 * \param name The name used to identify the texture.
 * \return The retrieved texture.
 */
Texture2D ResourceManager::GetTexture(const std::string& name)
{
    DFM_PROFILE_FUNCTION();
    return Get().m_textures[name];
}

/**
 * \brief Loads and returns a \code Shader object using the specified paths.
 * \param vertex_shader_path The path to the vertex shader code.
 * \param fragment_shader_path The path to the fragment shader code.
 * \return The loaded shader.
 */
Shader ResourceManager::LoadShaderFromFile(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    DFM_PROFILE_FUNCTION();

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

/**
 * \brief Loads and returns a \code Texture2D object using the specified path.
 * \param path The path to the texture.
 * \param alpha Determines if the texture has an alpha channel.
 * \param flip_on_load Determines if the texture should be flipped vertically upon load.
 * \return The loaded tecture.
 */
Texture2D ResourceManager::LoadTextureFromFile(const std::string& path, const bool alpha, const bool flip_on_load)
{
    DFM_PROFILE_FUNCTION();

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