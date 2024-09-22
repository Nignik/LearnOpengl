#pragma once

#include <vector>
#include <tuple>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

constexpr int sectorCount = 40;
constexpr int stackCount = 30;

namespace meshes
{
	inline std::vector<Vertex> generateVertices(float radius)
	{
		std::vector<Vertex> vertices;

		float x, y, z, xy;
		float nx, ny, nz;
		float lengthInv = 1.0f / radius;

		constexpr auto PI = glm::pi<float>();
		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;
			xy = radius * cosf(stackAngle);
			z = radius * sinf(stackAngle);

			for (int j = 0; j <= sectorCount; ++j)
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

		return vertices;
	}

	inline std::tuple<std::vector<int>, std::vector<int>> generateIndices()
	{
		std::vector<int> indices;
		std::vector<int> lineIndices;
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);
			k2 = k1 + sectorCount + 1;

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
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

				lineIndices.push_back(k1);
				lineIndices.push_back(k2);
				if (i != 0)
				{
					lineIndices.push_back(k1);
					lineIndices.push_back(k1 + 1);
				}
			}
		}

		return { indices, lineIndices };
	}

	inline std::tuple<std::vector<Vertex>, std::vector<unsigned int>> GenerateCube(glm::vec3 size)
	{
		std::vector<Vertex> vertices = {
			{ {-1.0f, -1.0f, -1.0f},  {0.0f,  0.0f, -1.0f} },
			{ { 1.0f, -1.0f, -1.0f},  {0.0f,  0.0f, -1.0f} },
			{ { 1.0f,  1.0f, -1.0f},  {0.0f,  0.0f, -1.0f} },
			{ {-1.0f,  1.0f, -1.0f},  {0.0f,  0.0f, -1.0f} },

			// Back face
			{ {-1.0f, -1.0f,  1.0f},  {0.0f,  0.0f,  1.0f} },
			{ {-1.0f,  1.0f,  1.0f},  {0.0f,  0.0f,  1.0f} },
			{ { 1.0f,  1.0f,  1.0f},  {0.0f,  0.0f,  1.0f} },
			{ { 1.0f, -1.0f,  1.0f},  {0.0f,  0.0f,  1.0f} },

			// Left face
			{ {-1.0f, -1.0f, -1.0f},  {-1.0f,  0.0f,  0.0f} },
			{ {-1.0f,  1.0f, -1.0f},  {-1.0f,  0.0f,  0.0f} },
			{ {-1.0f,  1.0f,  1.0f},  {-1.0f,  0.0f,  0.0f} },
			{ {-1.0f, -1.0f,  1.0f},  {-1.0f,  0.0f,  0.0f} },

			// Right face
			{ { 1.0f, -1.0f, -1.0f},  {1.0f,  0.0f,  0.0f} },
			{ { 1.0f, -1.0f,  1.0f},  {1.0f,  0.0f,  0.0f} },
			{ { 1.0f,  1.0f,  1.0f},  {1.0f,  0.0f,  0.0f} },
			{ { 1.0f,  1.0f, -1.0f},  {1.0f,  0.0f,  0.0f} },

			// Bottom face
			{ {-1.0f, -1.0f, -1.0f},  {0.0f, -1.0f,  0.0f} },
			{ {-1.0f, -1.0f,  1.0f},  {0.0f, -1.0f,  0.0f} },
			{ { 1.0f, -1.0f,  1.0f},  {0.0f, -1.0f,  0.0f} },
			{ { 1.0f, -1.0f, -1.0f},  {0.0f, -1.0f,  0.0f} },

			// Top face
			{ {-1.0f,  1.0f, -1.0f},  {0.0f,  1.0f,  0.0f} },
			{ { 1.0f,  1.0f, -1.0f},  {0.0f,  1.0f,  0.0f} },
			{ { 1.0f,  1.0f,  1.0f},  {0.0f,  1.0f,  0.0f} },
			{ {-1.0f,  1.0f,  1.0f},  {0.0f,  1.0f,  0.0f} }
		};

		for (auto& vert : vertices)
		{
			vert.Position.x *= size.x;
			vert.Position.y *= size.y;
			vert.Position.z *= size.z;
		}

		std::vector<unsigned int> indices = {
			// Front face
			0, 1, 2, 2, 3, 0,
			// Back face
			4, 5, 6, 6, 7, 4,
			// Left face
			8, 9, 10, 10, 11, 8,
			// Right face
			12, 13, 14, 14, 15, 12,
			// Bottom face
			16, 17, 18, 18, 19, 16,
			// Top face
			20, 21, 22, 22, 23, 20
		};

		std::tuple<std::vector<Vertex>, std::vector<unsigned int>> cube(vertices, indices);

		return cube;
	}

	inline Mesh generateQuad()
	{
		std::vector<Vertex> vertices = {
			{{-1.0f, -1.0f, 0.0f}},
			{{1.0f, -1.0f, 0.0f}},
			{{1.0f, 1.0f, 0.0f}},
			{{-1.0f, 1.0f, 0.0f}}
		};

		std::vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		return Mesh(vertices, indices);
	}
}