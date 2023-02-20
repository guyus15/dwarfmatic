#ifndef UBO_H
#define UBO_H

#include "rendering/shader.h"

#include "glad/glad.h"

#include <string>
#include <unordered_map>

class Ubo
{
public:
    Ubo();

    void Configure(std::string block_name, size_t size);
    void BindShaderBlock(const Shader& shader);
    void Create();
    void SetSubData(unsigned int offset, size_t size, const void* data) const;

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

class UboManager
{
public:
    static void Register(const std::string& name, const Ubo& ubo);
    [[nodiscard]] static Ubo& Retrieve(const std::string& name);

private:
    std::unordered_map<std::string, Ubo> m_registered_ubos;

    UboManager() = default;

    static UboManager& Get() { return s_instance; }
    static UboManager s_instance;
};

#endif // UBO_H