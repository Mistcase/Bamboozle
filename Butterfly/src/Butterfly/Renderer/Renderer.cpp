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
	Ref<Texture2D> skyTexture = nullptr;
	Ref<Object3D> sphere = nullptr;

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();

		auto shaders = Shaders::Create();
        shaders->createFromFile(Application::GetInstance().getResourcesDirectory().string() + "skybox_shader.glsl");
        skyboxShader = shaders->extract("skybox_shader"_hash).release();
		skyTexture = Texture2D::Create(Application::GetInstance().getResourcesDirectory() / "textures/sky.jpeg");
		sphere = std::make_shared<Object3D>(Application::GetInstance().getResourcesDirectory() / "objects/teapot.obj");
        sphere->setPosition({0.0f, 0.0f, 0.0f});
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

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
        RenderCommand::Clear();

		// static_cast<OpenGLShader*>(skyboxShader)->bind();
		// skyTexture->bind(0);
		// static_cast<OpenGLShader*>(skyboxShader)->setUniform1i("u_Skybox", 0);
		// static_cast<OpenGLShader*>(skyboxShader)->setUniformMat4("u_VP", viewProjection);
		// sphere->render();

		static_cast<OpenGLShader*>(Renderer2D::Shader())->bind();
        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform3f("u_CameraPosition", m_camera->getPosition());
		static_cast<OpenGLShader*>(Renderer2D::Shader())->setUniformMat4("u_VP", viewProjection);

		// static_cast<OpenGLShader*>(Renderer2D::Shader())->setUniform1i("u_Skybox", 0);
		// skyTexture->bind(0);
		// sphere->render();
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

	class Shader* CurrentShader()
	{
		return skyboxShader;
	}

} // namespace butterfly
