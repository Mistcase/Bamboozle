#include "Entity.h"

namespace butterfly
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_handle(handle)
		, m_scene(scene)
	{
	}

	Entity::operator bool() const
	{
		return m_handle != entt::null;
	}

} // namespace butterfly
