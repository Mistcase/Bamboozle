#include "Bamboozle/bbzlpch.h"
#include "Renderer.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/Renderer/PerspectiveCamera.h"
#include "Bamboozle/Renderer/Renderer2D.h"
#include "Bamboozle/Renderer/Shader.h"
#include "Bamboozle/Renderer/Shaders.h"
#include "Bamboozle/Renderer/Texture.h"
#include "Bamboozle/Renderer/VertexArray.h"
#include "Bamboozle/Transformable.h"
#include "Bamboozle/bbzl.h"

// Temp
#include "imgui.h"
#include "Bamboozle/DebugPanel.h"
#include "Bamboozle/Hash.h"
#include "Platform/OpenGL/OpenGLShader.h"

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
            static constexpr RenderAPI::API RenderApis[] = {
                RenderAPI::API::OpenGL,
                RenderAPI::API::Vulkan
            };

            const auto currentRenderAPI = Renderer::GetAPIName();
            const auto apiCount = std::size(RenderAPINames);

            const auto* apiName = std::find(std::begin(RenderAPINames), std::end(RenderAPINames), currentRenderAPI);
            int currentIndex = apiName - RenderAPINames;

            const auto apiChanged = ImGui::Combo("RenderAPI", &currentIndex, RenderAPINames, apiCount);
            if (apiChanged)
            {
                Renderer::SetGraphicsAPI(RenderApis[currentIndex]);
            }
        }
    } // namespace

    const PerspectiveCamera* Renderer::m_camera = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();

        auto shaders = Shaders::Create();
        shaders->createFromFile(Application::GetInstance().getResourceDirectory().string() + "skybox_shader.glsl");
        shaders->createFromFile(Application::GetInstance().getResourceDirectory().string() + "lines_shader.glsl");
        skyboxShader = shaders->extract("skybox_shader"_hash);

        BufferLayout primitiveVertexLayout{ { ShaderDataType::Float4, "a_Position" },
                                            { ShaderDataType::Float4, "a_Color" } };

        idleShader = shaders->extract("lines_shader"_hash);
        idleVertexBuffer = VertexBuffer::Create(2 * sizeof(PrimitiveVertex), nullptr);
        idleVertexBuffer->setLayout(primitiveVertexLayout);
        idleVertexArray = VertexArray::Create();
        idleVertexArray->addVertexBuffer(idleVertexBuffer);

        // Toggle render api from debug menu
        DebugPanel::Instance().registerSection("Renderer", []() {
            DebugDraw_GraphicsAPISection();
        });
    }

    void Renderer::Destroy()
    {
        Renderer2D::Destroy();
    }

    void Renderer::SetGraphicsAPI(RenderAPI::API api)
    {
        RenderCommand::Init(api);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(width, height);
    }

    void Renderer::BeginScene(const PerspectiveCamera* camera)
    {
        m_camera = camera;
        const auto& viewProjection = m_camera->getViewProjection();

        static_cast<OpenGLShader*>(Renderer2D::Shader())->bind();
		auto cameraPawn = m_camera->getPawn();
		const auto& transform = cameraPawn.getComponent<TransformComponent>();
        static_cast<bbzl::OpenGLShader*>(bbzl::Renderer::Shader())->setUniform3f("u_CameraPosition", transform.getPosition());
        static_cast<OpenGLShader*>(Renderer2D::Shader())->setUniformMat4("u_VP", viewProjection);

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        RenderCommand::Clear();
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
        RenderCommand::DrawPoints(idleVertexArray, 1);

        Shader()->bind();
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
        RenderCommand::DrawLines(idleVertexArray, 2);

        Shader()->bind();
    }

    class Shader* Renderer::Shader()
    {
        return Renderer2D::Shader(); // TODO: Give 3D renderer its own shader
    }

    class Shader* Renderer::SkyboxShader()
    {
        return skyboxShader.get();
    }

} // namespace bbzl
