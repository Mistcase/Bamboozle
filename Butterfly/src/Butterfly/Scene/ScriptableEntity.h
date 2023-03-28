#pragma once

#include "Butterfly/Scene/Entity.h"

namespace butterfly
{
	class ScriptableEntity
	{
	public:
		template <typename T>
			T& getComponent()
		{
			assert(hasComponent<T>());
			return m_entity.getComponent<T>();
		}

	private:
		Entity m_entity;
		friend class Scene;
	};
}
