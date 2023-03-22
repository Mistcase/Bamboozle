#include "Butterfly/Renderer/Texture.h"
#include "Butterfly/butterflypch.h"
#include "Renderer.h"

#include "Butterfly/Object3D.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Renderer/Renderer2D.h"
#include "Butterfly/Renderer/Shader.h"
#include "Butterfly/Renderer/VertexArray.h"

#include "Butterfly/Renderer/Shaders.h"
#include "Butterfly/Application.h"

//Temp
#include "Platform/OpenGL/OpenGLShader.h"
#include "Butterfly/Hash.h"

namespace butterfly
{
    namespace
    {
        std::unique_ptr<Shader> skyboxShader = nullptr;

        namespace Lines
        {
            struct Vertex
            {
                glm::vec4 position;
                glm::vec4 color;
            };

            Ref<VertexArray> vertexArray;
            Ref<VertexBuffer> vertexBuffer;

            std::unique_ptr<Shader> shader = nullptr;
        }
    }

    const PerspectiveCamera* Renderer::m_camera = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();

		auto shaders = Shaders::Create();
        shaders->createFromFile(Application::GetInstance().getResourcesDirectory().string() + "skybox_shader.glsl");
        shaders->createFromFile(Application::GetInstance().getResourcesDirectory().string() + "lines_shader.glsl");
        skyboxShader = shaders->extract("skybox_shader"_hash);

        Lines::shader = shaders->extract("lines_shader"_hash);
        Lines::vertexBuffer = VertexBuffer::Create(2 * sizeof(Lines::Vertex), nullptr);
        Lines::vertexBuffer->setLayout({
                { ShaderDataType::Float4, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }});
        Lines::vertexArray = VertexArray::Create();
        Lines::vertexArray->addVertexBuffer(Lines::vertexBuffer);
    }

    void Renderer::Destroy()
    {
        Renderer2D::Destroy();
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
        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform3f("u_CameraPosition", m_camera->getPosition());
		static_cast<OpenGLShader*>(Renderer2D::Shader())->setUniformMat4("u_VP", viewProjection);

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        RenderCommand::Clear();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::DrawLine(const Line& line)
    {
        assert(m_camera != nullptr);
        assert(Lines::shader != nullptr);

        Lines::shader->bind();
        static_cast<OpenGLShader*>(Lines::shader.get())->setUniformMat4("u_Transform", glm::mat4(1.0f));
        static_cast<OpenGLShader*>(Lines::shader.get())->setUniformMat4("u_VP", m_camera->getViewProjection());

        Lines::Vertex vertices[2] = {
            { glm::vec4(line.from, 1.0f), line.color },
            { glm::vec4(line.to, 1.0f), line.color }
        };
        Lines::vertexBuffer->setData(vertices, 2 * sizeof(Lines::Vertex));

        Lines::vertexArray->bind();
        RenderCommand::DrawLines(Lines::vertexArray, 2);

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

} // namespace butterfly
