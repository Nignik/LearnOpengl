#pragma once

#include <glad/glad.h>

#include "stb_image.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <map>
#include <set>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	[[nodiscard]]GLuint LoadTexture(const std::string& texturePath);
	void DestroyTexture(GLuint textureId);

private:
	GLenum GetTextureUnit();

	std::map<GLuint, std::shared_ptr<Texture>> m_TextureUnitsRegister;
	std::set<GLenum> m_AvailableTextureUnits;
};