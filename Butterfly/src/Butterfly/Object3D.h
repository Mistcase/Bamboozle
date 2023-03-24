#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Transformable.h"
#include "Butterfly/Renderer/Mesh.h"

#include <filesystem>

namespace butterfly
{
	class PerspectiveCamera;
	class Material;
	class Mesh;

	class Object3D : public Transformable
	{
	public:
		Object3D(const std::filesystem::path& path);

		void setMaterial(Ref<Material> material);

		virtual void update(float dt);
		virtual void render() const;

		Ref<Material> getMaterial() const;

	protected:
        Ref<Mesh> m_mesh;
        Ref<Material> m_material;
	};
}
