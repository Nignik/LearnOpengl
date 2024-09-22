#pragma once

#include <glm/glm.hpp>

#include <vector>

#include <IncludeEngine.h>

using namespace Color;
using glm::vec3;

inline std::map<std::string, Material> materials =
{
	{"Basic1", {GREEN, BLUE, BLUE, 0.5f}},
	{"Basic2", {BLUE, GREEN, GREEN, 0.5f}},
};


inline std::map<std::string, Light> lights = 
{
	{"Basic1", {vec3(1.0f), vec3(1.0f), vec3(1.0f), vec3(1.0f)}},
};