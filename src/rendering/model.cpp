#include "model.h"

#include "glad/glad.h"
#include "stb/stb_image.h"

#include <iostream>

static unsigned int TextureFromFile(const std::string& path, const std::string& directory);

void Model::Load(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_ALLOW_SHARED || !scene->mRootNode)
    {
        std::cerr << "Error: Failed to import model.\n" << importer.GetErrorString() << "\n";
    } else
    {
        std::cout << "Success: Loaded model " << path << ".\n";
    }

    m_directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::Draw(const Shader& shader) const
{
    for (const auto& mesh : m_meshes)
    {
        mesh.Draw(shader);
    }
}

void Model::ProcessNode(const aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(ProcessMesh(mesh, scene));
    }

    // Then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshTexture> textures;

    // Process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex{};

        glm::vec3 vector3{};
        vector3.x = mesh->mVertices[i].x;
        vector3.y = mesh->mVertices[i].y;
        vector3.z = mesh->mVertices[i].z;
        vertex.position = vector3;

        if (mesh->HasNormals())
        {
            vector3.x = mesh->mNormals[i].x;
            vector3.y = mesh->mNormals[i].y;
            vector3.z = mesh->mNormals[i].z;
            vertex.texture_coordinate = vector3;
        }

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vector2{};
            vector2.x = mesh->mTextureCoords[0][i].x;
            vector2.y = mesh->mTextureCoords[0][i].y;
            vertex.texture_coordinate = vector2;
        }
        else
        {
            vertex.texture_coordinate = glm::vec2{ 0.0f, 0.0f };
        }

        vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material
    if (scene->HasMaterials())
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<MeshTexture> diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

        std::vector<MeshTexture> specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

        std::vector<MeshTexture> normal_maps = LoadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
        textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

        std::vector<MeshTexture> height_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
        textures.insert(textures.end(), height_maps.begin(), height_maps.end());
    }

    return Mesh{ vertices, indices, textures };
}

std::vector<MeshTexture> Model::LoadMaterialTextures(const aiMaterial* material, const aiTextureType type,
                                                     const std::string& type_name)
{
    std::vector<MeshTexture> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;

        // Check if the texture has previously been loaded, if so, skip.
        for (const auto& loaded_texture : m_loaded_textures)
        {
            if (std::strcmp(m_loaded_textures[i].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(loaded_texture);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            MeshTexture texture;
            texture.id = TextureFromFile(str.C_Str(), m_directory);
            texture.type = type_name;
            texture.path = str.C_Str();

            textures.push_back(texture);
            m_loaded_textures.push_back(texture);
        }
    }

    return textures;
}

unsigned int TextureFromFile(const std::string& path, const std::string& directory)
{
    // TODO: Convert texture usage to Texture2D implementation.

    std::string filename = path;
    filename = directory + '/' + filename;

    unsigned int texture_id;
    glGenTextures(1, &texture_id);

    int width, height, nr_components;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nr_components, 0);

    if (data)
    {
        GLenum format = 0;
        if (nr_components == 1)
        {
            format = GL_RED;
        } else if (nr_components == 3)
        {
            format = GL_RGB;
        } else if (nr_components == 4)
        {
            format = GL_RGBA;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Error: Failed to load texture at path: " << path << "\n";
        stbi_image_free(data);
    }

    return texture_id;
}