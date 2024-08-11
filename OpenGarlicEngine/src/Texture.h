#pragma once

#include <glad/glad.h>
#include <memory>

struct Texture
{
	Texture(GLuint id, GLenum unit);

	GLuint id;
	GLenum unit;
};