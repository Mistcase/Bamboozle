#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json_fwd.hpp>

namespace bbzl
{
	class Texture2D;

	// Must be default constructible type
	class Sprite
	{
	public:
		void draw(glm::vec2 position, glm::vec2 scale, float rotation) const;

		bool isValid() const { return m_texture != nullptr; }
		uint32_t getHashId() const { return m_hashId; }

	private:
		Texture2D* m_texture = nullptr;
		glm::vec2 m_position;
		[[deprecated]] glm::vec2 m_size;

		uint32_t m_hashId;

		friend class Atlas;
		friend void to_json(nlohmann::json& j, const Sprite& sprite);
		friend void from_json(const nlohmann::json& j, Sprite& sprite);

	};

} // namespace bbzl
