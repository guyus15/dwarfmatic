#include "mesh.h"

#include "glad/glad.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<MeshTexture> textures)
    : m_vertices{ std::move(vertices) },
    m_indices{ std::move(indices) },
    m_textures{ std::move(textures) },
    m_vao{}, m_vbo{}, m_ebo{}
{
    SetupMesh();
}

void Mesh::Draw(const Shader& shader) const
{
    unsigned int diffuse_nr = 1;
    unsigned int specular_nr = 1;
    unsigned int normal_nr = 1;
    unsigned int height_nr = 1;

    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        // Activate correct texture unit before binding.
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = m_textures[i].type;

        if (name == "texture_diffuse")
        {
            number = std::to_string(specular_nr++);
        }
        else if (name == "texture_specular")
        {
            number = std::to_string(specular_nr++);
        }
        else if (name == "texture_normal")
        {
            number = std::to_string(normal_nr++);
        }
        else if (name == "texture_height")
        {
            number = std::to_string(height_nr++);
        }

        shader.SetInt((name + number), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(nullptr));

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinate));

    glBindVertexArray(0);
}