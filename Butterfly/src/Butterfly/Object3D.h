#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Transformable.h"
#include "Butterfly/Renderer/Mesh.h"

#include <filesystem>

namespace butterfly
{
	class PerspectiveCamera;
	class Mesh;

	class Object3D : public Transformable
	{
	public:
		Object3D(const std::filesystem::path& path);

		virtual void update(float dt);
		virtual void render() const;

	protected:
        Ref<Mesh> m_mesh;
        Material m_material;
	};
}
