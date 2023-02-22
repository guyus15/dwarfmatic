/**
 * \file resource_manager.h
 */

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "rendering/shader.h"
#include "rendering/texture2d.h"

#include <unordered_map>

/**
 * \brief A singleton class used to provide methods for loading and accessing resources.
 */
class ResourceManager
{
public:
    /**
     * \brief Loads and gets a \code Shader at a particular path.
     * \param name The name used to identify the shader.
     * \param vertex_shader_path The path to the vertex shader code.
     * \param fragment_shader_path The path to the fragment shader code.
     * \return The loaded shader.
     */
    static Shader LoadShader(const std::string& name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);

    /**
     * \brief Gets a shader with the specified name.
     * \param name The name used to identify the shader.
     * \return The retrieved shader.
     */
    static Shader& GetShader(const std::string& name);

    /**
     * \brief Loads and gets a \code Texture2D at a particular path.
     * \param name The name used to identify the texture.
     * \param path The path to the texture.
     * \param alpha Determines if the texture has an alpha channel.
     * \param flip_on_load Determines if the texture should be flipped vertically upon load.
     * \return The loaded texture.
     */
    static Texture2D LoadTexture(const std::string& name, const std::string& path, bool alpha, bool flip_on_load = false);

    /**
     * \brief Gets a texture with the specified name.
     * \param name The name used to identify the texture.
     * \return The retrieved texture.
     */
    static Texture2D GetTexture(const std::string& name);

private:
    std::unordered_map<std::string, Shader> m_shaders;
    std::unordered_map<std::string, Texture2D> m_textures;

    ResourceManager() = default;

    /**
     * \brief Loads and returns a \code Shader object using the specified paths.
     * \param vertex_shader_path The path to the vertex shader code.
     * \param fragment_shader_path The path to the fragment shader code.
     * \return The loaded shader.
     */
    static Shader LoadShaderFromFile(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

    /**
     * \brief Loads and returns a \code Texture2D object using the specified path.
     * \param path The path to the texture.
     * \param alpha Determines if the texture has an alpha channel.
     * \param flip_on_load Determines if the texture should be flipped vertically upon load.
     * \return The loaded tecture.
     */
    static Texture2D LoadTextureFromFile(const std::string& path, bool alpha, bool flip_on_load);

    /**
     * \brief Gets a reference to the singleton instance.
     * \return The singleton instance.
     */
    static ResourceManager& Get() { return s_instance; }

    static ResourceManager s_instance;
};

#endif // RESOURCE_MANAGER_H