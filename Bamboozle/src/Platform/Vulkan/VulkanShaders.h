#pragma once

#include "Bamboozle/Renderer/Shaders.h"

namespace bbzl
{
    class VulkanDevice;
    class VulkanShader;

    class VulkanShaders : public Shaders
    {
    public:
        VulkanShaders(VulkanDevice& device);
        ~VulkanShaders() override;

        // This implementation only load precompiled SPIR-V file. Call it for every single shader (vertex, fragment)
        Shader* createFromFile(const std::filesystem::path& filepath) override;

        Shader* get(uint32_t id) override;
        std::unique_ptr<Shader> extract(uint32_t id) override;

    private:
        using Container = std::unordered_map<uint32_t, std::unique_ptr<VulkanShader>>;
        Container m_shaders;

        VulkanDevice& m_device;
    };

} // namespace bbzl