#pragma once

#include "RenderAPI.h"

namespace bubble
{
    class RenderCommand
    {
    public:
        static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
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
