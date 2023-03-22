#include "Butterfly/butterflypch.h"
#include "Skybox.h"

#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Renderer/Shader.h"
#include "Butterfly/Renderer/Texture.h"
#include "Butterfly/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace
{
	std::unique_ptr<butterfly::Shader> skyboxShader;

} // namespace

namespace butterfly
{
	SkyBox::SkyBox(const std::filesystem::path& sphere, const std::filesystem::path& texture, const PerspectiveCamera* camera)
		: Object3D(sphere)
		, m_texture(Texture2D::Create(texture.generic_string()))
		, m_camera(camera)
	{
		assert(m_camera != nullptr);
		assert(m_texture != nullptr);
	}

	void SkyBox::update(float dt)
	{
		setPosition(m_camera->getPosition());
		Object3D::update(dt);
	}

	void SkyBox::render() const
	{
		Renderer::SkyboxShader()->bind();

		static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniformMat4("u_Transform", m_transform);
		static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniformMat4("u_VP", m_camera->getViewProjection());
		static_cast<OpenGLShader*>(Renderer::SkyboxShader())->setUniform1i("u_SkyBox", 0);

		m_texture->bind(0);
		m_mesh->draw();

		Renderer::Shader()->bind();
	}

} // namespace butterfly
