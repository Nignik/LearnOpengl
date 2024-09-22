#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Mesh.h"
#include "Shader.h"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

using glm::vec2, glm::vec3;

class Model
{
public:
	Model(std::string const& path, bool gamma = false);
	Model(std::shared_ptr<Mesh> mesh);
	void Draw(std::shared_ptr<Shader> shader);

private:
	std::vector<std::shared_ptr<Texture>> m_Textures_loaded;
	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::string m_Directory;
	bool m_GammaCorrection = true;

	void m_LoadModel(std::string const& path);
	void m_ProcessNode(aiNode* node, const aiScene* scene);
	std::shared_ptr<Mesh> m_ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> m_LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};