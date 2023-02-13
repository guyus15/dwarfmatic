#include "shader.h"
#include "utils/gl_debug.h"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>

Shader::Shader()
    : m_id{}, m_compiled{ false }
{
}

void Shader::Compile(const std::string& vertex_shader_code, const std::string& fragment_shader_code)
{
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
        std::cerr << "Error: Vertex shader compilation failed.\n" << info_log << "\n";
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cerr << "Error: Fragment shader compilation failed.\n" << info_log << "\n";
    }

    m_id = glCreateProgram();

    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 512, nullptr, info_log);
        std::cerr << "Error: Failed link shader program.\n" << info_log << "\n";
    } else
    {
        m_compiled = true;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::Use() const
{
    if (!m_compiled)
    {
        std::cerr << "Error: Shader has not been compiled successfully.\n";
        return;
    }

    glUseProgram(m_id);
}

void Shader::SetBool(const std::string& name, const bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, const int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, const float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const float value1, const float value2, const float value3) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value1, value2, value3);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetMat4(const std::string& name, glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}