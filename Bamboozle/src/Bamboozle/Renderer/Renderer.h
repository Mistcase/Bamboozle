#pragma once

#include "RenderCommand.h"
#include "Bamboozle/Assert.h"

namespace bbzl
{
    class Camera;
    class Shader;
    class VertexArray;
    class Object3D;
    class PerspectiveCamera;

    /*enum class RendererAPI
    {
        None,
        OpenGL,
        Vulkan
    };*/

    class Renderer
    {
    public:
        struct Line
        {
            glm::vec3 from;
            glm::vec3 to;
            glm::vec4 color;
        };

    public:
        static inline RenderAPI::API GetAPI()
        {
            return RenderAPI::GetAPI();
        }

        static inline const char* GetAPIName()
        {
            switch (RenderAPI::GetAPI())
            {
            case RenderAPI::API::OpenGL:
                return "OpenGL";
            case RenderAPI::API::Vulkan:
                return "Vulkan";

            default:
                ASSERT(!"Unknown render api");
            }

            return "%ERROR_MSG%";
        }

        static void Init();
        static void Destroy();

        static void SetGraphicsAPI(RenderAPI::API api);

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(const PerspectiveCamera* camera);
        static void EndScene();

		static void DrawPoint(const glm::vec3& position, const glm::vec4& color);
        static void DrawLine(const Line& line);

        static class Shader* Shader();
        static class Shader* SkyboxShader();

    private:
        static const PerspectiveCamera* m_camera;
    };

} // namespace bbzl
