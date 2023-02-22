/**
 * \file shader.cpp
 */

#include "shader.h"
#include "utils/logging.h"
#include "utils/profiling.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>

Shader::Shader()
    : m_id{}, m_compiled{ false }
{

}

/**
 * \brief Compiles the vertex and fragment shader code.
 * \param vertex_shader_code The vertex shader code.
 * \param fragment_shader_code The fragment shader code.
 */
void Shader::Compile(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
{
    DFM_PROFILE_FUNCTION();

    const char* vertex_code_c = vertex_shader_code.c_str();
    const char* fragment_code_c = fragment_shader_code.c_str();

    int success = 0;
    char info_log[512];

    const GLint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_code_c, nullptr);
    glShaderSource(fragment_shader, 1, &fragment_code_c, nullptr);

    glCompileShader(vertex_shader);
    glCompileShader(fragment_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        DFM_CORE_ERROR("Failed to compile vertex shader.\n{0}", info_log);
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        DFM_CORE_ERROR("Failed to compile fragment shader.\n{0}", info_log);
    }

    m_id = glCreateProgram();

    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, info_log);
        DFM_CORE_ERROR("Failed to link shader program.\n{0}", info_log);
    } else
    {
        m_compiled = true;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

/**
 * \brief Uses the shader program for rendering.
 */
void Shader::Use() const
{
    DFM_PROFILE_FUNCTION();

    if (!m_compiled)
    {
        DFM_CORE_ERROR("Failed to use uncompiled shader.");
        return;
    }

    glUseProgram(m_id);
}

/**
 * \brief Set a boolean uniform in the shader program.
 * \param name The name of the uniform.
 * \param value The value to set the uniform to.
 */
void Shader::SetBool(const std::string& name, const bool value) const
{
    DFM_PROFILE_FUNCTION();
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), static_cast<int>(value));
}

/**
 * \brief Sets an integer uniform in the shader program.
 * \param name The name of the uniform.
 * \param value The value to set the uniform to.
 */
void Shader::SetInt(const std::string& name, const int value) const
{
    DFM_PROFILE_FUNCTION();
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

/**
 * \brief Sets an float uniform in the shader program.
 * \param name The name of the uniform.
 * \param value The value to set the uniform to.
 */
void Shader::SetFloat(const std::string& name, const float value) const
{
    DFM_PROFILE_FUNCTION();
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

/**
 * \brief Sets a vec3 uniform in the shader program.
 * \param name The name of the uniform.
 * \param value1 The vec3 x value.
 * \param value2 The vec3 y value.
 * \param value3 The vec3 z value.
 */
void Shader::SetVec3(const std::string& name, const float value1, const float value2, const float value3) const
{
    DFM_PROFILE_FUNCTION();
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value1, value2, value3);
}

/**
* \brief Sets an vec3 uniform in the shader program.
* \param name The name of the uniform.
* \param value The value to set the uniform to.
*/
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    DFM_PROFILE_FUNCTION();
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
}

/**
 * \brief Sets an mat4 uniform in the shader program.
 * \param name The name of the uniform.
 * \param value The value to set the uniform to.
 */
void Shader::SetMat4(const std::string& name, glm::mat4& value) const
{
    DFM_PROFILE_FUNCTION();
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/**
 * \brief Gets the ID of the shader program.
 * \return The shader program's ID.
 */
GLint Shader::GetId() const
{
    return m_id;
}