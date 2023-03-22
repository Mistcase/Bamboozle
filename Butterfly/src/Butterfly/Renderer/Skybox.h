#pragma once

#include "Butterfly/Object3D.h"

#include <filesystem>

namespace butterfly
{
	class PerspectiveCamera;
	class Texture2D;

	class SkyBox final : public Object3D
	{
	public:
		SkyBox(const std::filesystem::path& sphere, const std::filesystem::path& texture, const PerspectiveCamera* camera);

		void update(float dt) override;
		void render() const override;

	private:
		butterfly::Ref<Texture2D> m_texture;
		const PerspectiveCamera* m_camera;
	};

} // namespace butterfly
