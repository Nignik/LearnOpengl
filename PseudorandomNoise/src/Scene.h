#pragma once

#include <IncludeEngine.h>

#include <algorithm>
#include <numeric>

#include "SmallXXHash.h"

class Scene
{
public:
	Scene();
	
	void Render();
	void GenerateMesh();

	int GetRes() const;
	void SetRes(int res);
	int GetSeed() const;
	void SetSeed(int seed);
	float GetVerticalOffset() const;
	void SetVerticalOffset(float offset);
	std::shared_ptr<Transform> GetDomainTrs();

private:
	std::shared_ptr<Shader> m_hashShader;
	std::shared_ptr<Material> m_material;
	std::unique_ptr<InstancedMesh> m_iMesh{};

	int m_res = 32;
	float m_invRes = 1.0f / m_res;
	int m_amount = m_res * m_res;
	int m_seed = 0;
	float m_verticalOffset = 0.0f;

	std::shared_ptr<Transform> m_domainTrs;

	std::vector<SmallXXHash> m_hashes{};
	std::vector<glm::mat4> m_transforms{};

	void ComputeHashes();
	void ComputeTransforms();
};