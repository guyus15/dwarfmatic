#ifndef MESH_H
#define MESH_H

#include "shader.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coordinate;
};

struct MeshTexture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);

    void Draw(const Shader& shader) const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<MeshTexture> m_textures;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;

    void SetupMesh();
};

#endif // MESH_H