#pragma once

#include "RenderCommand.h"

namespace butterfly
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

        static void Init();
        static void Destroy();

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(const Camera* camera);
        static void EndScene();

        static void Submit(const Shader* shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

    private:
        static const Camera* m_camera;
    };

} // namespace butterfly