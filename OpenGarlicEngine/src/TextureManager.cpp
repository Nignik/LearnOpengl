#include "TextureManager.h"

#include <filesystem>

TextureManager::TextureManager()
	: m_AvailableTextureUnits({GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7 })
{
}

GLuint TextureManager::LoadTexture(const std::string& texturePath)
{
	unsigned int textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Error: Failed to load texture: " << stbi_failure_reason() << std::endl;
	}

	GLenum textureUnit = GetTextureUnit();
	if (textureUnit == -1)
		std::cerr << "Error: no available texture units" << std::endl;

	std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureId, textureUnit);
	m_TextureUnitsRegister[texture->id] = texture;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	return texture->id;
}

GLenum TextureManager::GetTextureUnit()
{
	if (m_AvailableTextureUnits.empty())
		return -1;

	GLenum textureUnit = *m_AvailableTextureUnits.begin();

	return textureUnit;
}

void TextureManager::DestroyTexture(GLuint textureId)
{
	GLenum textureUnit = m_TextureUnitsRegister[textureId]->unit;
	m_AvailableTextureUnits.insert(textureUnit);
	m_TextureUnitsRegister.erase(textureId);
}



