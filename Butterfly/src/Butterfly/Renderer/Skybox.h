#pragma once

// #include "Butterfly/Object3D.h"
#include "Butterfly/Core.h"
#include <filesystem>

namespace butterfly
{
    class PerspectiveCamera;
    class Texture2D;

    class SkyBox final
    {
    public:
        SkyBox(const std::filesystem::path& sphere, const std::filesystem::path& texture, const PerspectiveCamera* camera);
//        void render();

    private:
        butterfly::Ref<Texture2D> m_texture;
        const PerspectiveCamera* m_camera;
    };

} // namespace butterfly
