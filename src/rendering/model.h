/**
 * \file model.h
 */

#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"

#include <string>
#include <vector>

/**
 * \brief Represents a 3D model.
 */
class Model
{
public:
    Model() = default;

    /**
     * \brief Loads the model from the specified file path.
     * \param path The path to the model file.
     */
    void Load(const std::string& path);

    /**
     * \brief Draws the model with the specified shader.
     * \param shader The shader used to render the model.
     */
    void Draw(const Shader& shader) const;

private:
    std::vector<Mesh> m_meshes;
    std::vector<MeshTexture> m_loaded_textures;
    std::string m_directory;

    /**
     * \brief Processes the nodes of the model.
     * \param node The node to be processed.
     * \param scene The scene of the model.
     */
    void ProcessNode(const aiNode* node, const aiScene* scene);

    /**
     * \brief Processes the meshes of the model.
     * \param mesh The mesh to be processed.
     * \param scene The scene of the model.
     * \return The processed mesh.
     */
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    /**
     * \brief Loads the textures of the material.
     * \param material The material of the model.
     * \param type The type of texture.
     * \param type_name The name of the type of texture.
     * \return The loaded textures.
     */
    std::vector<MeshTexture> LoadMaterialTextures(const aiMaterial* material, aiTextureType type, const std::string& type_name);
};

#endif // MODEL_H