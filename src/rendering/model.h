#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include "texture.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <string>
#include <vector>

class Model
{
public:
    Model() = default;

    void Load(const std::string& path);
    void Draw(const Shader& shader) const;

private:
    std::vector<Mesh> m_meshes;
    std::vector<MeshTexture> m_loaded_textures;
    std::string m_directory;

    void ProcessNode(const aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<MeshTexture> LoadMaterialTextures(const aiMaterial* material, aiTextureType type, const std::string& type_name);
};

#endif // MODEL_H