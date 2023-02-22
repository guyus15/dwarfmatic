/**
 * \file mesh.h
 */

#ifndef MESH_H
#define MESH_H

#include "shader.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <string>
#include <vector>

/**
 * \brief Represents a vertex in a 3D model.
 */
struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coordinate;
};

/**
 * \brief Represents a texture that is used to draw a mesh.
 */
struct MeshTexture
{
    unsigned int id{};
    std::string type;
    std::string path;
};

/**
 * \brief Represents a mesh in a 3D model.
 */
class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);

    /**
     * \brief Draws the mesh using the given shader.
     * \param shader The shader used to draw the mesh.
     */
    void Draw(const Shader& shader) const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<MeshTexture> m_textures;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    /**
     * \brief Sets up the mesh by creating and binding a vertex array object (VAO), vertex buffer object (VBO),
     * and element buffer object (EBO).
     */
    void SetupMesh();
};

#endif // MESH_H