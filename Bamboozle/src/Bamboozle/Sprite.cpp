#include "bbzlpch.h"
#include "Sprite.h"

#include "Bamboozle/Renderer/Renderer2D.h"
#include "Bamboozle/Renderer/Texture.h"

namespace bbzl
{
	void Sprite::draw(glm::vec2 position, glm::vec2 scale, float rotation) const
	{
		const auto textureWidth = m_texture->getWidth();
		const auto textureHeight = m_texture->getHeight();

		glm::vec4 uv{
			m_position.x / textureWidth,
			m_position.y / textureHeight,
			(m_position.x + m_size.x) / textureWidth,
			(m_position.y + m_size.y) / textureHeight
		};

		const glm::vec4 white{ 1.0f, 1.0f, 1.0f, 1.0f };
		Renderer2D::DrawQuad(glm::vec3(position, 0.0f), scale, rotation, white, m_texture, uv);
	}

} // namespace bbzl
