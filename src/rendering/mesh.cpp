/**
 * \file mesh.cpp
 */

#include "mesh.h"
#include "utils/profiling.h"

#include "glad/glad.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<MeshTexture> textures)
    : m_vertices{ std::move(vertices) },
    m_indices{ std::move(indices) },
    m_textures{ std::move(textures) },
    m_vao{}, m_vbo{}, m_ebo{}
{
    SetupMesh();
}

/**
 * \brief Draws the mesh using the given shader.
 * \param shader The shader used to draw the mesh.
 */
void Mesh::Draw(const Shader& shader) const
{
    DFM_PROFILE_FUNCTION();

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
            number = std::to_string(diffuse_nr++);
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

        shader.SetInt(name + number, static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    // Draw mesh
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

/**
 * \brief Sets up the mesh by creating and binding a vertex array object (VAO), vertex buffer object (VBO),
 * and element buffer object (EBO).
 */
void Mesh::SetupMesh()
{
    DFM_PROFILE_FUNCTION();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // Vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture_coordinate));

    glBindVertexArray(0);
}