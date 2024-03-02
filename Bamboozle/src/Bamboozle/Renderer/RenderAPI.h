#pragma once

#include "Bamboozle/Core.h"
#include <glm/glm.hpp>
#include <memory>

namespace bbzl
{
    class RenderDevice;
    class VertexArray;

    class RenderAPI
    {
    public:
        enum class API_TYPE
        {
            None,
            OpenGL,
            Vulkan,

            Default = Vulkan,
        };

        inline static API_TYPE GetAPI()
        {
            return m_renderAPIType;
        };

        static API_TYPE m_renderAPIType;
    };

} // namespace bbzl
