/**
 * \file shader.h
 */


#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/mat4x4.hpp"

#include <string>

/**
 * \brief Represents a shader program.
 */
class Shader
{
public:
    Shader();

    /**
     * \brief Compiles the vertex and fragment shader code.
     * \param vertex_shader_code The vertex shader code.
     * \param fragment_shader_code The fragment shader code.
     */
    void Compile(const std::string& vertex_shader_code, const std::string& fragment_shader_code);

    /**
     * \brief Uses the shader program for rendering.
     */
    void Use() const;

    /**
     * \brief Set a boolean uniform in the shader program.
     * \param name The name of the uniform.
     * \param value The value to set the uniform to.
     */
    void SetBool(const std::string& name, bool value) const;

    /**
     * \brief Sets an integer uniform in the shader program.
     * \param name The name of the uniform.
     * \param value The value to set the uniform to.
     */
    void SetInt(const std::string& name, int value) const;

    /**
     * \brief Sets an float uniform in the shader program.
     * \param name The name of the uniform.
     * \param value The value to set the uniform to.
     */
    void SetFloat(const std::string& name, float value) const;

    /**
     * \brief Sets a vec3 uniform in the shader program.
     * \param name The name of the uniform.
     * \param value1 The vec3 x value.
     * \param value2 The vec3 y value. 
     * \param value3 The vec3 z value. 
     */
    void SetVec3(const std::string& name, float value1, float value2, float value3) const;

    /**
     * \brief Sets an vec3 uniform in the shader program.
     * \param name The name of the uniform.
     * \param value The value to set the uniform to.
     */
    void SetVec3(const std::string& name, const glm::vec3& value) const;

    /**
     * \brief Sets an mat4 uniform in the shader program.
     * \param name The name of the uniform.
     * \param value The value to set the uniform to.
     */
    void SetMat4(const std::string& name, glm::mat4& value) const;

    /**
     * \brief Gets the ID of the shader program.
     * \return The shader program's ID.
     */
    [[nodiscard]] GLint GetId() const;

private:
    GLint m_id;
    bool m_compiled;
};

#endif // SHADER_H