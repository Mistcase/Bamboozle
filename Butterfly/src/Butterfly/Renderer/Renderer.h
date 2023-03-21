#pragma once

#include "RenderCommand.h"

namespace butterfly
{
    class Camera;
    class Shader;
    class VertexArray;
	class Object3D;
	class PerspectiveCamera;

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

        static void BeginScene(const PerspectiveCamera* camera);
        static void EndScene();

        static class Shader* Shader();
		static class Shader* SkyboxShader();

    private:
        static const PerspectiveCamera* m_camera;
    };

} // namespace butterfly
