#include "bbzlpch.h"
#include "Atlas.h"

#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Texture.h"
#include "Bamboozle/Hash.h"
#include "Bamboozle/Helpers.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace bbzl // Sprite <-> Json conversion
{
    void to_json(json& j, const Sprite& sprite) {
        j = json{ { "id", sprite.hashId },
				 { "x", sprite.pos.x },
				 { "y", sprite.pos.y },
		         { "w", sprite.size.x },
		         { "h", sprite.size.y } };
    }

    void from_json(const json& j, Sprite& sprite) {
		// Do not use exceptions
        j["id"].get_to(sprite.hashId);
		j["x"].get_to(sprite.pos.x);
		j["y"].get_to(sprite.pos.y);
		j["w"].get_to(sprite.size.x);
		j["h"].get_to(sprite.size.y);
    }

} // namespace bbzl

namespace bbzl
{
	Atlas::Atlas(const char* path)
		: Resource(hash(path))
	{
		// Atlas file is just a json with array of sprites
		// For now read it from drive
	    auto data = helpers::ReadEntireFile(path);
		if (data == nullptr)
		{
			BBZL_CORE_ERROR("Atlas %s not loaded", path);
			return;
		}

		// Parse
		const auto root = json::parse(data);

		const auto pathToTexture = root["path_to_texture"].get<std::string>();
		m_texture = Texture2D::Create(pathToTexture, Texture2D::Format::RGB);
		if (m_texture == nullptr)
		{
			BBZL_CORE_ERROR("Atlas %s not loaded", path);
			return;
		}

		const auto& jsonSprites = root["sprites"];
		BBZL_ASSERT(jsonSprites.is_array());

		for (const auto& jsonSprite : jsonSprites)
		{
			m_sprites.emplace_back() = jsonSprite;
		}

		BBZL_CORE_INFO("Atlas %s loaded", path);
	}

	Atlas::~Atlas()
	{
		delete m_texture;
	}

	Sprite* Atlas::findSprite(uint32_t hashId)
	{
		auto it = std::find_if(m_sprites.begin(), m_sprites.end(), [hashId](Sprite& sprite){ return sprite.hashId == hashId; });
		return it != m_sprites.end() ? &*it : nullptr;
	}

} // namespace bbzl
