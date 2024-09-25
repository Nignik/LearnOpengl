#include "Drawable.h"

extern Global::ObjectsManager* g_objectsManager;

Drawable::Drawable(std::shared_ptr<Model> model, std::shared_ptr<Transform> transform, std::shared_ptr<Material> material)
	: m_model(model),
	m_transform(transform),
	m_material(material),
	m_id(g_objectsManager->GenerateObjectId())
{
}

void Drawable::Draw()
{
	auto& frameData = Global::FrameData::GetInstance();
	if (m_material)
	{
		m_material->SetMVP(m_transform->GetTransformMatrix(), frameData.view, frameData.projection);
		m_material->SetShaderParameter("viewPos", frameData.position);
		m_material->Use();
		m_model->Draw(m_material->GetShader());
	}
	else
	{
		std::cerr << "No material has been set" << std::endl;
	}
}

