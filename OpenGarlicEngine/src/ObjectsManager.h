#pragma once

#include <vector>
#include <map>
#include <memory>

namespace Global
{
	class ObjectsManager
	{
	public:
		ObjectsManager(const ObjectsManager&) = delete;
		ObjectsManager& operator=(const ObjectsManager&) = delete;

		static void Init();
		static void Shutdown();

		static uint32_t GenerateObjectId();
		//static uint32_t GenerateHandleIdx();

		static ObjectsManager& GetInstance();

	protected:
		ObjectsManager();
		~ObjectsManager();

		uint32_t m_CurrentObjectId = 1;
		uint32_t m_CurrentHandleIdx = 1;

		//std::map<int, std::shared_ptr<Drawable>> m_drawables;
	};
}

