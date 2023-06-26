#include "Entity.h"

namespace bbzl
{
	Entity::Entity(entt::entity handle, entt::registry* registry)
		: m_handle(handle)
		, m_registry(registry)
	{
	}

	Entity::operator bool() const
	{
		return m_handle != entt::null && m_registry->valid(m_handle);
	}

} // namespace bbzl
