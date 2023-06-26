#pragma once

#include <entt/entt.hpp>

namespace bbzl
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, entt::registry* registry);

		template <typename T, typename... Args>
		T& addComponent(Args&&... args)
		{
			assert(!hasComponent<T>());
			return m_registry->emplace<T>(m_handle, std::forward<Args>(args)...);
		}

		template <typename T>
		T& getComponent()
		{
			assert(hasComponent<T>());
			return m_registry->get<T>(m_handle);
		}

        template <typename T>
        const T& getComponent() const
        {
            assert(hasComponent<T>());
			return m_registry->get<T>(m_handle);
        }

		template <typename T>
		bool hasComponent() const
		{
			return m_registry->any_of<T>(m_handle);
		}

		template <typename T>
		void removeComponent()
		{
			assert(hasComponent<T>());
			m_registry->remove<T>(m_handle);
		}

		operator bool() const;

	private:
		entt::entity m_handle = entt::null;
		entt::registry* m_registry = nullptr;

        friend class PerspectiveCamera;
	};

} // namespace bbzl
