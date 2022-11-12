#pragma once

#include "RenderCommand.h"

namespace bubble
{
    class Camera;
    class Shader;
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

        static void BeginScene(const Camera* camera, const Shader* shader);
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    };

} // namespace bubble
