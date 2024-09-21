#include "ObjectsManager.h"

namespace Global
{
	static ObjectsManager* g_objectsManager;

	void ObjectsManager::Init()
	{
		g_objectsManager = new ObjectsManager();
	}

	void ObjectsManager::Shutdown()
	{
		delete g_objectsManager;
		g_objectsManager = nullptr;
	}

	uint32_t ObjectsManager::GenerateObjectId()
	{
		return g_objectsManager->m_CurrentObjectId++;
	}

	//uint32_t ObjectsManager::GenerateHandleIdx()
	//{
	//	return g_objectsManager->m_CurrentHandleIdx++;
	//}

	ObjectsManager& ObjectsManager::GetInstance()
	{
		return *g_objectsManager;
	}

	ObjectsManager::ObjectsManager()
	{

	}

	ObjectsManager::~ObjectsManager()
	{

	}

}