#pragma once

// #include "Bamboozle/Object3D.h"
#include "Bamboozle/Core.h"
#include <filesystem>

namespace bbzl
{
    class PerspectiveCamera;
    class Texture2D;

    class SkyBox final
    {
    public:
        SkyBox(const std::filesystem::path& sphere, const std::filesystem::path& texture, const PerspectiveCamera* camera);
//        void render();

    private:
        bbzl::Ref<Texture2D> m_texture;
        const PerspectiveCamera* m_camera;
    };

} // namespace bbzl
