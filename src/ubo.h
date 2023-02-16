#ifndef UBO_H
#define UBO_H

#include "rendering/shader.h"

#include "glad/glad.h"

#include <string>
#include <vector>

class Ubo
{
public:
    Ubo(std::string block_name, size_t size);

    void BindShaderBlock(const Shader& shader);
    void Create();
    void SetSubData(int offset, size_t size, const void* data) const;

    [[nodiscard]] unsigned int GetId() const;

private:
    std::string m_block_name;
    std::vector<GLint> m_binded_shader_ids;
    unsigned int m_id;
    unsigned int m_binding_point;
    size_t m_size;

    void Bind() const;

    static void Unbind();
    static unsigned int s_binding_point;
};

#endif // UBO_H