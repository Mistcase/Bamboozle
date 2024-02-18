#pragma once

#include "Bamboozle/Renderer/Shaders.h"

namespace bbzl
{
    class VulkanShader;

    class VulkanShaders : public Shaders
    {
    public:
        ~VulkanShaders() override;

        Shader* createFromFile(const std::filesystem::path& filepath) override;
        Shader* get(uint32_t id) override;
        std::unique_ptr<Shader> extract(uint32_t id) override;

    private:
        using SourcePair = std::pair<std::string, std::string>;

        std::string loadSource(const std::filesystem::path& filepath) const;
        SourcePair preprocess(const std::string& source) const;
        VulkanShader* build(const std::string& name, const SourcePair& sources);

    private:
        using Container = std::unordered_map<uint32_t, std::unique_ptr<VulkanShader>>;
        Container m_shaders;
    };

} // namespace bbzl