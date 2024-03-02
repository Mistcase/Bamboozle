#include "Bamboozle/bbzlpch.h"

#include "Platform/Vulkan/VulkanContext.h"

// Corresponding header.h
#include "Renderer.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/Renderer/PerspectiveCamera.h"
#include "Bamboozle/Renderer/Renderer2D.h"
#include "Bamboozle/Renderer/Shader.h"
#include "Shader.h"
#include "Bamboozle/Renderer/VertexArray.h"
#include "Bamboozle/Transformable.h"
#include "Bamboozle/bbzl.h"

// Temp
#include "Device.h"
#include "DeviceExecutionContextFwd.h"
#include "DeviceFwd.h"
#include "imgui.h"
#include "PipelineState.h"
#include "RenderAPI.h"
#include "ShaderPass.h"
#include "TextureManager.h"
#include "Bamboozle/DebugPanel.h"
#include "Bamboozle/Hash.h"
#include "Passes/PassTest.h"


#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/OpenGL/OpenGLDevice.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/Vulkan/vkDevice.h"
#include "Platform/Vulkan/vkExecutionContext.h"

namespace bbzl
{
    namespace
    {
        std::unique_ptr<Shader> skyboxShader = nullptr;

        //struct PrimitiveVertex
        //{
        //    glm::vec4 position;
        //    glm::vec4 color;
        //};

        std::unique_ptr<Shader> idleShader = nullptr;
        Ref<VertexArray> idleVertexArray;
        Ref<VertexBuffer> idleVertexBuffer;

    } // namespace

    namespace // Renderer debug draw
    {
        void DebugDraw_GraphicsAPISection()
        {
            // Order of arrays elements matters
            static constexpr char* RenderAPINames[] = {
                "OpenGL",
                "Vulkan"
            };
            static constexpr RenderAPI::API_TYPE RenderApis[] = {
                RenderAPI::API_TYPE::OpenGL,
                RenderAPI::API_TYPE::Vulkan
            };

            const auto currentRenderAPI = Renderer::GetAPIName();
            const auto apiCount = std::size(RenderAPINames);

            const auto* apiName = std::find(std::begin(RenderAPINames), std::end(RenderAPINames), currentRenderAPI);
            int currentIndex = apiName - RenderAPINames;

            const auto apiChanged = ImGui::Combo("RenderAPI", &currentIndex, RenderAPINames, apiCount);
            if (apiChanged)
            {
                Renderer::OnAPIChanged(RenderApis[currentIndex]);
            }
        }
    } // namespace

    std::vector<std::unique_ptr<ShaderPass>> Renderer::m_shaderPasses{};
    const PerspectiveCamera* Renderer::m_camera = nullptr;

    void Renderer::Init()
    {
        OnAPIChanged(RenderAPI::API_TYPE::Default);
        InitShaderPasses();

        TextureManager::Init(*g_RenderDevice);
        Renderer2D::Init();

        // Toggle render api from debug menu
        DebugPanel::Instance().registerSection("Renderer", []() {
            DebugDraw_GraphicsAPISection();
        });
    }

    void Renderer::Destroy()
    {
        delete g_RenderDevice;
        delete g_RenderContext;

        Renderer2D::Destroy();
    }

    void Renderer::OnAPIChanged(RenderAPI::API_TYPE api)
    {
        RenderAPI::m_renderAPIType = api; // TODO: REMOVE

        if (api == RenderAPI::API_TYPE::OpenGL)
        {
            ASSERT_FAIL("Implement OpenGlRenderContext");
        }
        else if (api == RenderAPI::API_TYPE::Vulkan)
        {
            auto* vk_device = new vkDevice(Application::GetInstance().getWindow());
            g_RenderContext = new vkDeviceExecutionContext(*vk_device);
        }

        ASSERT(g_RenderDevice != nullptr);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        //RenderCommand::SetViewport(width, height);
    }

    void Renderer::SwapBuffers()
    {
        g_RenderDevice->swapBuffers();
    }

    void Renderer::FrameBegin()
    {
        g_RenderContext->beginFrame();
        // g_RenderDevice->beginFrame();

        // TODO: add opegl context
        if (g_RenderContext)
        {
            // g_RenderContext->beginFrame();
            g_RenderContext->beginRenderPass();
        }
    }

    void Renderer::FrameEnd()
    {
        // TODO: add opegl context
        if (g_RenderContext)
        {
            // g_RenderContext->endRenderPass();
            g_RenderContext->endFrame();
        }

        // g_RenderDevice->endFrame();
        g_RenderContext->endFrame();
    }

    void Renderer::BeginScene(const PerspectiveCamera* camera)
    {
        // g_RenderContext->bindPipeline(*m_pso);
        m_camera = camera;
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Texture2D* texture, const glm::vec4& uv)
    {
        // Setup VF, pipeline, render pass, ...
        PreparePass(ShaderPassType::PASS_COMMON);

        // Draw call
        g_RenderContext->draw(6, 1);
    }

    void Renderer::DrawPoint(const glm::vec3& position, const glm::vec4& color)
    {
        // Temporary use idleShader
      /*  assert(m_camera != nullptr);
        assert(idleShader != nullptr);

        idleShader->bind();
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_Transform", glm::mat4(1.0f));
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_VP", m_camera->getViewProjection());

        PrimitiveVertex vertex{ glm::vec4(position, 1.0f), color };
        idleVertexBuffer->setData(&vertex, sizeof(vertex));

        idleVertexArray->bind();*/
        //RenderCommand::DrawPoints(idleVertexArray, 1);

        // Shader()->bind();
    }

    void Renderer::DrawLine(const Line& line)
    {
       /* assert(m_camera != nullptr);
        assert(idleShader != nullptr);

        idleShader->bind();
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_Transform", glm::mat4(1.0f));
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_VP", m_camera->getViewProjection());

        PrimitiveVertex vertices[2] = {
            { glm::vec4(line.from, 1.0f), line.color },
            { glm::vec4(line.to, 1.0f), line.color }
        };
        idleVertexBuffer->setData(vertices, 2 * sizeof(PrimitiveVertex));

        idleVertexArray->bind();*/
        //RenderCommand::DrawLines(idleVertexArray, 2);

        // Shader()->bind();
    }

    void Renderer::InitShaderPasses()
    {
        m_shaderPasses.resize(size_t(ShaderPassType::COUNT));
        m_shaderPasses[size_t(ShaderPassType::PASS_COMMON)] = std::make_unique<ShaderPassCommon>();
    }

    void Renderer::PreparePass(ShaderPassType pass)
    {
        const auto idx = static_cast<size_t>(pass);
        m_shaderPasses[idx]->prepare(); 
    }

} // namespace bbzl
