#pragma once

namespace bbzl
{
	class Resource;
    class Sprite;
	// To be implemented: class Sound;
	// To be implemented: class Stream;
	// To be implemented: class Video;

	class ResourceSystem
	{
	public:
		ResourceSystem() = default;
		~ResourceSystem();

		uint32_t loadBundle(const std::string& path);
		void unloadBundle(uint32_t hashId);

		const Sprite* getSprite(uint32_t hashId) const;
		// const Sound* getSound(uint32_t hashId) const;

	private:
		void LoadAtlas(const char* path);

	private:
		std::unordered_map<uint32_t, Resource*> m_resources; // Replace by vector?
		std::unordered_map<uint32_t, std::vector<uint32_t>> m_bundles;

		// Resource: { atlas, sound, video }
		std::unordered_map<uint32_t, const Sprite*> m_sprites;

#if defined(DEBUG)
	private:
		std::set<std::string> m_dbgBundlePaths;
#endif
	};

} // namespace bbzl
