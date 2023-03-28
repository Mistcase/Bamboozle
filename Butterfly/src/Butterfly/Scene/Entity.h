#pragma once

#include "Butterfly/Scene.h"

namespace butterfly
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);

		template <typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			assert(!hasComponent<T>());
			m_scene->m_registry.emplace(m_handle, std::forward<Args>(args)...);
		}

		template <typename T>
		T& getComponent()
		{
			assert(hasComponent<T>());
			return m_scene->m_registry.get<T>(m_handle);
		}

		template <typename T>
		bool hasComponent()
		{
			return m_scene->m_registry.any_of<T>();
		}

		template <typename T>
		void removeComponent()
		{
			assert(hasComponent<T>());
			m_scene->m_registry.remove<T>(m_handle);
		}

		operator bool() const;

	private:
		entt::entity m_handle = entt::null;
		Scene* m_scene;
	};

} // namespace butterfly
