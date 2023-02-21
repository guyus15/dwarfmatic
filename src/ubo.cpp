#include "ubo.h"
#include "utils/profiling.h"

unsigned int Ubo::s_binding_point = 0;

Ubo::Ubo()
    : m_block_name{},
    m_id{ 0 },
    m_binding_point{ 0 },
    m_size{ 0 }
{
}

void Ubo::Configure(std::string block_name, const size_t size)
{
    DFM_PROFILE_FUNCTION();

    m_block_name = std::move(block_name);
    m_binding_point = s_binding_point;
    m_size = size;

    s_binding_point++;
}

void Ubo::BindShaderBlock(const Shader& shader)
{
    DFM_PROFILE_FUNCTION();

    const GLint shader_id = shader.GetId();
    const unsigned int uniform_block_index = glGetUniformBlockIndex(shader_id, m_block_name.c_str());
    glUniformBlockBinding(shader_id, uniform_block_index, m_binding_point);

    m_binded_shader_ids.push_back(shader_id);
}

void Ubo::Create()
{
    DFM_PROFILE_FUNCTION();

    glGenBuffers(1, &m_id);

    Bind();
    glBufferData(GL_UNIFORM_BUFFER, static_cast<GLsizeiptr>(m_size), nullptr, GL_STATIC_DRAW);
    Unbind();

    glBindBufferRange(GL_UNIFORM_BUFFER, m_binding_point, m_id, 0, m_size);
}

void Ubo::SetSubData(const unsigned int offset, const size_t size, const void* data) const
{
    DFM_PROFILE_FUNCTION();

    Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, static_cast<GLsizeiptr>(size), data);
    Unbind();
}

void Ubo::Bind() const
{
    DFM_PROFILE_FUNCTION();
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void Ubo::Unbind()
{
    DFM_PROFILE_FUNCTION();
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

unsigned int Ubo::GetId() const
{
    return m_id;
}

UboManager UboManager::s_instance;

void UboManager::Register(const std::string& name, const Ubo& ubo)
{
    DFM_PROFILE_FUNCTION();
    Get().m_registered_ubos[name] = ubo;
}

Ubo& UboManager::Retrieve(const std::string& name)
{
    DFM_PROFILE_FUNCTION();
    return Get().m_registered_ubos[name];
}
