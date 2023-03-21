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
    const PerspectiveCamera* Renderer::m_camera = nullptr;
	Shader* skyboxShader = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();

		auto shaders = Shaders::Create();
        shaders->createFromFile(Application::GetInstance().getResourcesDirectory().string() + "skybox_shader.glsl");
        skyboxShader = shaders->extract("skybox_shader"_hash).release();
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

    class Shader* Renderer::Shader()
    {
        return Renderer2D::Shader(); // TODO: Give 3D renderer its own shader
    }

	class Shader* Renderer::SkyboxShader()
	{
		return skyboxShader;
	}

} // namespace butterfly
