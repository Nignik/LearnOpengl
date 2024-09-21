#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../Mesh.h"

constexpr auto PI = glm::pi<float>();

namespace Procedural
{
	inline std::shared_ptr<Mesh> SphereMesh(float radius, uint32_t sectorCount = 40, uint32_t stackCount = 30)
	{
		std::vector<Vertex> vertices;

		float x, y, z, xy;
		float nx, ny, nz;
		float lengthInv = 1.0f / radius;

		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		for (uint32_t i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;
			xy = radius * cosf(stackAngle);
			z = radius * sinf(stackAngle);

			for (uint32_t j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;

				x = xy * cosf(sectorAngle);
				y = xy * sinf(sectorAngle);

				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;

				vertices.emplace_back(glm::vec3(x, y, z), glm::vec3(nx, ny, nz));
			}
		}

		std::vector<uint32_t> indices;
		int k1, k2;
		for (uint32_t i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);
			k2 = k1 + sectorCount + 1;

			for (uint32_t j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				if (i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				if (i != (stackCount - 1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}

		return std::make_shared<Mesh>(vertices, indices);
	}
}