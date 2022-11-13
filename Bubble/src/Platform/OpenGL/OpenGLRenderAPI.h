#pragma once

#include "Bubble/Renderer/RenderAPI.h"

namespace bubble
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void init() override;

        void setClearColor(const glm::vec4& color) override;
        void clear() override;

        void drawIndexed(const Ref<VertexArray>& vertexArray) override;
    };

} // namespace bubble
