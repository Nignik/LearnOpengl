#include "Scene.h"

Scene::Scene()
	: m_hashShader(std::make_shared<Shader>("shaders/hash.vs", "shaders/hash.fs")),
	m_domainTrs(std::make_shared<Transform>())
{
	m_material = std::make_shared<Material>(m_hashShader);

	GenerateMesh();
}

void Scene::Render()
{
	m_iMesh->Draw();
}

void Scene::GenerateMesh()
{
	ComputeHashes();
	ComputeTransforms();

	auto mesh = Procedural::CubeMesh();
	m_iMesh = std::make_unique<InstancedMesh>(mesh, m_material, m_amount);

	std::vector<uint32_t> h;
	h.reserve(m_hashes.size());
	for (auto& hash : m_hashes)
	{
		h.push_back(hash);
	}

	m_iMesh->AddSsbo(m_transforms);
	m_iMesh->AddSsbo(h);
}

int Scene::GetRes() const
{
	return m_res;
}

void Scene::SetRes(int res)
{
	m_res = res;
	m_invRes = 1.0f / m_res;
	m_amount = m_res * m_res;

	GenerateMesh();
}

int Scene::GetSeed() const
{
	return m_seed;
}

void Scene::SetSeed(int seed)
{
	m_seed = seed;

	GenerateMesh();
}

float Scene::GetVerticalOffset() const
{
	return m_verticalOffset;
}

void Scene::SetVerticalOffset(float offset)
{
	m_verticalOffset = offset;

	GenerateMesh();
}

std::shared_ptr<Transform> Scene::GetDomainTrs()
{
	return m_domainTrs;
}

void Scene::SetDomainPosition(glm::vec3 position)
{
	m_domainTrs->SetPosition(position);
	GenerateMesh();
}

void Scene::SetDomainRotation(glm::vec3 rotation)
{
	m_domainTrs->Rotate(rotation);
	GenerateMesh();
}

void Scene::SetDomainScale(glm::ivec3 scale)
{
	m_domainTrs->SetScale(scale);
	GenerateMesh();
}

void Scene::ComputeHashes()
{
	m_hashes.clear();

	m_hashes.reserve(m_amount);
	for (int i = 0; i < m_amount; i++)
	{
		float vf = floor(m_invRes * i + 0.00001);
		float uf = m_invRes * (i - m_res * vf + 0.5f) - 0.5f;
		vf = m_invRes * (vf + 0.5f) - 0.5f;

		vec4 p = m_domainTrs->GetTransformMatrix() * vec4( uf, 0.0f, vf, 1.0f );

		uint32_t u = (int)floor(p.x);
		uint32_t v = (int)floor(p.z);

		m_hashes.push_back(SmallXXHash(m_seed).Eat(u).Eat(v));
	}
}

void Scene::ComputeTransforms()
{
	m_transforms.clear();

	m_transforms.reserve(m_amount);
	for (int i = 0; i < m_res; i++)
	{
		for (int j = 0; j < m_res; j++)
		{
			float yOffset = ((1.0 / 255.0) * (m_hashes[i * m_res + j] >> 24) - 0.5) * m_verticalOffset;
			Transform t(vec3(1.0f * i, yOffset, 1.0f * j), 0.0f, 0.0f, 0.0f, vec3(1.0f));
			m_transforms.push_back(t.GetTransformMatrix());
		}
	}
}
