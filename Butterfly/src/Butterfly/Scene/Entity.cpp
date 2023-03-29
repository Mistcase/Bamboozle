#include "Entity.h"

namespace butterfly
{
	Entity::Entity(entt::entity handle, entt::registry* registry)
		: m_handle(handle)
		, m_registry(registry)
	{
	}

	Entity::operator bool() const
	{
		return m_handle != entt::null;
	}

} // namespace butterfly
