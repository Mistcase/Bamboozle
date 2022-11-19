#pragma once

#include "Bubble/Renderer/RenderAPI.h"

namespace bubble
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void init() override;

        void setViewport(uint32_t left, uint32_t bottom, uint32_t width, uint32_t height) override;

        void setClearColor(const glm::vec4& color) override;
        void clear() override;

        void drawIndexed(const Ref<VertexArray>& vertexArray) override;
        void drawIndexed(const Ref<VertexArray>& vertexArray, size_t count) override;
    };

} // namespace bubble
