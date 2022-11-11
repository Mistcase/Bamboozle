#pragma once

#include "RenderCommand.h"

namespace bubble
{
    class VertexArray;

    enum class RendererAPI
    {
        None,
        OpenGL
    };

    class Renderer
    {
    public:
        static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    };

} // namespace bubble
