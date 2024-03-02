#pragma once

#include <filesystem>

namespace bbzl
{
    class RenderDevice;
}

namespace bbzl
{
    class Shader;

    class Shaders
    {
    public:
        // TODO: Remove default value
        static std::unique_ptr<Shaders> Create(RenderDevice* device = nullptr);

        virtual ~Shaders() = default;

        virtual Shader* createFromFile(const std::filesystem::path& filepath) = 0;
        virtual Shader* get(uint32_t id) = 0;
        virtual std::unique_ptr<Shader> extract(uint32_t id) = 0;
    };
}; // namespace bbzl
