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

        static void BeginScene(const Camera* camera);
        static void EndScene();

        static void Submit(const Shader* shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform);

    private:
        static const Camera* m_camera;
    };

} // namespace bubble
