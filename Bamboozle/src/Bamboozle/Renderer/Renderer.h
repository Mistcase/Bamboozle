#pragma once

#include "RenderAPI.h"
#include "Bamboozle/Assert.h"

namespace bbzl
{
    class VidDeviceInterface;
    class DeviceExecutionContextInterface;

    class Camera;
    class Shader;
    class VertexArray;
    class Object3D;
    class PerspectiveCamera;
    class Texture2D;

    struct PipelineState;

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
        static inline RenderAPI::API_TYPE GetAPI()
        {
            return RenderAPI::GetAPI();
        }

        static inline const char* GetAPIName()
        {
            switch (RenderAPI::GetAPI())
            {
            case RenderAPI::API_TYPE::OpenGL:
                return "OpenGL";
            case RenderAPI::API_TYPE::Vulkan:
                return "Vulkan";

            default:
                ASSERT_FAIL("Unknown render api");
            }

            return "%ERROR_MSG%";
        }

        static void Init();
        static void Destroy();

        static void OnAPIChanged(RenderAPI::API_TYPE api);

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void SwapBuffers();

        static void FrameBegin();
        static void FrameEnd();

        static void BeginScene(const PerspectiveCamera* camera);
        static void EndScene();

        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Texture2D* texture, const glm::vec4& uv);
		static void DrawPoint(const glm::vec3& position, const glm::vec4& color);
        static void DrawLine(const Line& line);

        // static class Shader* Shader();
        static class Shader* SkyboxShader();

    private:
        static std::unique_ptr<VidDeviceInterface> m_device;
        static std::unique_ptr<DeviceExecutionContextInterface> m_deviceContext;

        // static std::unique_ptr<RenderAPI> m_renderAPI;
        static const PerspectiveCamera* m_camera;
        static PipelineState* m_pso;

        static Shader* m_defaultVertexShader;
        static Shader* m_defaultFragmentShader;
    };

} // namespace bbzl
