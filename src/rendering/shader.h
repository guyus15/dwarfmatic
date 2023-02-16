#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/mat4x4.hpp"

#include <string>

class Shader
{
public:
    Shader();

    void Compile(const std::string& vertex_shader_code, const std::string& fragment_shader_code);
    void Use() const;
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, float value1, float value2, float value3) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetMat4(const std::string& name, glm::mat4& value) const;

    [[nodiscard]] GLint GetId() const;

private:
    GLint m_id;
    bool m_compiled;
};

#endif // SHADER_H