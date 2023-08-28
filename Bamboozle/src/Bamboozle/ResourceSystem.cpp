#include "bbzlpch.h"
#include "ResourceSystem.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/Atlas.h"
#include "Bamboozle/Core.h"
#include "Bamboozle/Hash.h"
#include "Bamboozle/Helpers.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Resource.h"

#include <nlohmann/json.hpp>

// Atlas, sound, video

namespace
{
	enum class AssetType
	{
		None,
		Atlas,
		Sound,
		Video
	};

	AssetType GetAssetTypeFromPath(const char* path)
	{
#define CHECK_SUBSTR_RETURN(str, retval) if (strstr(path, str) != nullptr) { return retval; }
		CHECK_SUBSTR_RETURN("atlases", AssetType::Atlas);
		CHECK_SUBSTR_RETURN("sounds", AssetType::Sound);
		CHECK_SUBSTR_RETURN("videos", AssetType::Video);
#undef CHECK_SUBSTR_RETURN

		return AssetType::None;
	}

} // namespace

namespace bbzl
{
	ResourceSystem::~ResourceSystem()
	{
		for (auto [_hash, resource] : m_resources)
		{
			resource->ReleaseRef();
		}
	}

	uint32_t ResourceSystem::loadBundle(const std::string& path)
	{
		// For now read it from drive
	    auto data = helpers::ReadEntireFile(path.c_str());
		if (data.empty())
		{
            BBZL_ASSERT(!"Fail to load bundle");
			return 0;
		}

		// Parse
		const auto bundleHash = hash(data);
		const auto json = nlohmann::json::parse(data);

		const auto& jsonAssets = json["assets"];
		BBZL_ASSERT(jsonAssets.is_array());

        // Create resource instances
		for (auto asset : jsonAssets)
		{
            const auto assetPath = asset.get<std::string>();
			const auto assetType = GetAssetTypeFromPath(assetPath.c_str());

			switch (assetType)
			{
			case AssetType::Atlas:
				LoadAtlas(assetPath.c_str());
				break;

			default:
                BBZL_ASSERT(!"Unknown type");
				break;
			}
		}

		return bundleHash;
	}

	void ResourceSystem::unloadBundle(uint32_t hashId)
	{
		auto itBundle = m_bundles.find(hashId);
		if (itBundle == m_bundles.cend())
		{
			return;
		}

		const auto& resources = itBundle->second;
		for (auto resId : resources)
		{
			auto itResource = m_resources.find(resId);
			if (itResource == m_resources.cend())
			{
				BBZL_CORE_WARN("Try to unload not loaded bundle");
				return;
			}

			auto resource = itResource->second;
			const auto isAlive = resource->ReleaseRef();
			if (!isAlive)
			{
				m_resources.erase(itResource);
			}
		}

		m_bundles.erase(itBundle);

#if defined(DEBUG)
        for (auto it = m_dbgBundlePaths.begin(); it != m_dbgBundlePaths.end(); ++it)
		{
            if (hash(*it) == hashId)
			{
				m_dbgBundlePaths.erase(it);
				break;
			}
		}
#endif
	}

	const Sprite* ResourceSystem::getSprite(uint32_t hashId) const
	{
		auto it = m_sprites.find(hashId);
		return it != m_sprites.cend() ? it->second : nullptr;
	}

	void ResourceSystem::LoadAtlas(const char* path)
	{
		BBZL_ASSERT(GetAssetTypeFromPath(path) == AssetType::Atlas);

		auto atlas = new Atlas((Application::GetInstance().getResourceDirectory() / path).c_str() );

		for (const auto& sprite : *atlas)
		{
            const auto hash = sprite.getHashId();
			BBZL_ASSERT(m_sprites.find(hash) == m_sprites.cend());
			m_sprites[hash] = &sprite;
		}

		m_resources[atlas->getHashId()] = atlas;
	}

} // namespace bbzl
