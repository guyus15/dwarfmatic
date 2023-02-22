/**
 * \file ubo.h
 */

#ifndef UBO_H
#define UBO_H

#include "rendering/shader.h"

#include "glad/glad.h"

#include <string>
#include <unordered_map>

/**
 * \brief A wrapper for a GL uniform buffer object.
 */
class Ubo
{
public:
    Ubo();

    /**
     * \brief Configures the UBO with the given block name and size.
     * \param block_name The name of the UBO block.
     * \param size The size of the UBO block.
     */
    void Configure(std::string block_name, size_t size);

    /**
     * \brief Binds the UBO to the given shader.
     * \param shader The shader to be bound with the UBO.
     */
    void BindShaderBlock(const Shader& shader);

    /**
     * \brief Creates a buffer object for the UBO.
     */
    void Create();

    /**
     * \brief Sets a subrange of the UBO data.
     * \param offset The offset of the UBO data subrange.
     * \param size The size of the UBO data subrange
     * \param data The data to be loaded into the subrange.
     */
    void SetSubData(unsigned int offset, size_t size, const void* data) const;

    /**
     * \brief Gets the ID of the UBO.
     * \return The UBO's ID.
     */
    [[nodiscard]] unsigned int GetId() const;

private:
    std::string m_block_name;
    std::vector<GLint> m_binded_shader_ids;
    unsigned int m_id;
    unsigned int m_binding_point;
    size_t m_size;

    /**
     * \brief Binds the UBO object.
     */
    void Bind() const;

    /**
     * \brief Unbinds the UBO object.
     */
    static void Unbind();

    static unsigned int s_binding_point;
};

/**
 * \brief A singleton class used to manage \code Ubo objects.
 */
class UboManager
{
public:
    /**
     * \brief Registers the given UBO with the specified name in the manager.
     * \param name The name used to identify the UBO.
     * \param ubo The UBO to be managed.
     */
    static void Register(const std::string& name, const Ubo& ubo);

    /**
     * \brief Retrieves the \code Ubo object using the specified name.
     * \param name The name used to identify the UBO.
     * \return The retrieved UBO.
     */
    [[nodiscard]] static Ubo& Retrieve(const std::string& name);

private:
    std::unordered_map<std::string, Ubo> m_registered_ubos;

    UboManager() = default;

    /**
     * \brief Gets the singleton instance.
     * \return The singleton instance.
     */
    static UboManager& Get() { return s_instance; }
    static UboManager s_instance;
};

#endif // UBO_H