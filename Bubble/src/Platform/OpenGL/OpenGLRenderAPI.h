#pragma once

#include "Bubble/Renderer/RenderAPI.h"

namespace bubble
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
         void setClearColor(const glm::vec4& color) override;
         void clear() override;

         void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

} // namespace bubble
