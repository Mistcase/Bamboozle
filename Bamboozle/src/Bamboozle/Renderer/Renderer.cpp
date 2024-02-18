#include "Bamboozle/bbzlpch.h"
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
#include "imgui.h"
#include "PipelineState.h"
#include "RenderAPI.h"
#include "Bamboozle/DebugPanel.h"
#include "Bamboozle/Hash.h"
#include "Platform/OpenGL/OpenGLDevice.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/Vulkan/VulkanDevice.h"
#include "Platform/Vulkan/VulkanDeviceExecutionContext.h"

namespace bbzl
{
    namespace
    {
        std::unique_ptr<Shader> skyboxShader = nullptr;

        struct PrimitiveVertex
        {
            glm::vec4 position;
            glm::vec4 color;
        };

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

    namespace
    {
        using ShaderData = std::vector<std::byte>;
        ShaderData LoadEntireFile(const std::filesystem::path& path)
        {
            std::ifstream ifs(path, std::ios::ate | std::ios::binary);
            ASSERT(ifs.is_open());

            ShaderData buffer(ifs.tellg());

            ifs.seekg(0);
            ifs.read((char*)buffer.data(), buffer.size());
            ifs.close();

            return buffer;
        }
    }

    std::unique_ptr<VidDeviceInterface> Renderer::m_device;
    std::unique_ptr<DeviceExecutionContextInterface> Renderer::m_deviceContext;

    Shader* Renderer::m_defaultVertexShader;
    Shader* Renderer::m_defaultFragmentShader;

    PipelineState* Renderer::m_pso = nullptr;
    const PerspectiveCamera* Renderer::m_camera = nullptr;

    void Renderer::Init()
    {
        OnAPIChanged(RenderAPI::API_TYPE::Default);

        // TODO: Resource system (Load file)?
        m_defaultVertexShader = m_device->createShader(Shader::Type::Vertex, LoadEntireFile(Application::GetInstance().getResourceDirectory() / "shaders\\shader.vert.spv"));
        m_defaultFragmentShader = m_device->createShader(Shader::Type::Pixel, LoadEntireFile(Application::GetInstance().getResourceDirectory() / "shaders\\shader.frag.spv"));

        // TODO: Is it correct to init pso once here?
        m_pso = m_device->createPipelineStateObject();

        Renderer2D::Init();

        // Toggle render api from debug menu
        DebugPanel::Instance().registerSection("Renderer", []() {
            DebugDraw_GraphicsAPISection();
        });
    }

    void Renderer::Destroy()
    {
        m_device->destroyShader(m_defaultVertexShader);
        m_device->destroyShader(m_defaultFragmentShader);

        Renderer2D::Destroy();
    }

    void Renderer::OnAPIChanged(RenderAPI::API_TYPE api)
    {
        RenderAPI::m_renderAPIType = api; // TODO: REMOVE

        if (api == RenderAPI::API_TYPE::OpenGL)
        {
            m_device = std::make_unique<OpenGLDevice>();
            m_deviceContext = std::make_unique<DeviceExecutionContextInterface>();
        }
        else if (api == RenderAPI::API_TYPE::Vulkan)
        {
            m_device = std::make_unique<VulkanDevice>(Application::GetInstance().getWindow());
            m_deviceContext = std::make_unique<VulkanDeviceExecutionContext>(*(VulkanDevice*)m_device.get());
        }

        ASSERT(m_device != nullptr);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        //RenderCommand::SetViewport(width, height);
    }

    void Renderer::SwapBuffers()
    {
        m_device->swapBuffers();
    }

    void Renderer::FrameBegin()
    {
        m_device->beginFrame();

        // TODO: add opegl context
        if (m_deviceContext)
        {
            m_deviceContext->beginFrame();
            m_deviceContext->beginRenderPass();
        }

        // TODO: Fix shaders
        m_pso->primTopologyType = PipelineState::PrimitiveTopologyType::Triangles;
        m_pso->shaderBundle[Shader::Type::Vertex] = m_defaultVertexShader;
        m_pso->shaderBundle[Shader::Type::Pixel] = m_defaultFragmentShader;
        m_pso->validate();
    }

    void Renderer::FrameEnd()
    {
        // TODO: add opegl context
        if (m_deviceContext)
        {
            m_deviceContext->endRenderPass();
            m_deviceContext->endFrame();
        }

        m_device->endFrame();
    }

    void Renderer::BeginScene(const PerspectiveCamera* camera)
    {
        m_pso->bind();

        m_camera = camera;
        const auto& viewProjection = m_camera->getViewProjection();

        /*static_cast<OpenGLShader*>(Renderer2D::Shader())->bind();
		auto cameraPawn = m_camera->getPawn();
		const auto& transform = cameraPawn.getComponent<TransformComponent>();
        static_cast<OpenGLShader*>(bbzl::Renderer::Shader())->setUniform3f("u_CameraPosition", transform.getPosition());
        static_cast<OpenGLShader*>(Renderer2D::Shader())->setUniformMat4("u_VP", viewProjection);*/

        //RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        //RenderCommand::Clear();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::DrawPoint(const glm::vec3& position, const glm::vec4& color)
    {
        // Temporary use idleShader
        assert(m_camera != nullptr);
        assert(idleShader != nullptr);

        idleShader->bind();
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_Transform", glm::mat4(1.0f));
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_VP", m_camera->getViewProjection());

        PrimitiveVertex vertex{ glm::vec4(position, 1.0f), color };
        idleVertexBuffer->setData(&vertex, sizeof(vertex));

        idleVertexArray->bind();
        //RenderCommand::DrawPoints(idleVertexArray, 1);

        // Shader()->bind();
    }

    void Renderer::DrawLine(const Line& line)
    {
        assert(m_camera != nullptr);
        assert(idleShader != nullptr);

        idleShader->bind();
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_Transform", glm::mat4(1.0f));
        static_cast<OpenGLShader*>(idleShader.get())->setUniformMat4("u_VP", m_camera->getViewProjection());

        PrimitiveVertex vertices[2] = {
            { glm::vec4(line.from, 1.0f), line.color },
            { glm::vec4(line.to, 1.0f), line.color }
        };
        idleVertexBuffer->setData(vertices, 2 * sizeof(PrimitiveVertex));

        idleVertexArray->bind();
        //RenderCommand::DrawLines(idleVertexArray, 2);

        // Shader()->bind();
    }

    //class Shader* Renderer::Shader()
    //{
    //    return Renderer2D::Shader(); // TODO: Give 3D renderer its own shader
    //}

    class Shader* Renderer::SkyboxShader()
    {
        return skyboxShader.get();
    }

} // namespace bbzl
