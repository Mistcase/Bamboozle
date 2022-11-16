#pragma once

#include "RenderAPI.h"

namespace bubble
{
    class RenderCommand
    {
    public:
        static inline void Init()
        {
            m_renderAPI->init();
        }

        static inline void SetViewport(uint32_t width, uint32_t height)
        {
            m_renderAPI->setViewport(0, 0, width, height);
        }

        static inline void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            m_renderAPI->drawIndexed(vertexArray);
        }

        static inline void SetClearColor(const glm::vec4& color)
        {
            m_renderAPI->setClearColor(color);
        }

        static inline void Clear()
        {
            m_renderAPI->clear();
        }

    private:
        static RenderAPI* m_renderAPI;
    };

} // namespace bubble
