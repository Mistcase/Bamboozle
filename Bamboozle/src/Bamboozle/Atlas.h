#pragma once

#include "Bamboozle/Resource.h"

#include <glm/glm.hpp>
#include <vector>

namespace bbzl
{
	class Texture2D;

	// Must be default constructible type
	struct Sprite
	{
		Texture2D* texture;
		glm::vec2 pos;
		glm::vec2 size;

		uint32_t hashId;
	};

	class Atlas final : public Resource
	{
	public:
		using SpriteContainer = std::vector<Sprite>;

	public:
		Atlas(const char* path);
		~Atlas();

		Sprite* findSprite(uint32_t hashId);

		SpriteContainer::const_iterator begin() const { return m_sprites.begin(); }
		SpriteContainer::const_iterator end() const { return m_sprites.end(); }

	private:
		std::vector<Sprite> m_sprites;
		Texture2D* m_texture = nullptr;
	};

} // namespace bbzl
