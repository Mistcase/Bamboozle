#pragma once

#include <filesystem>

namespace butterfly
{
    class Shader;

    class Shaders
    {
    public:
        static std::unique_ptr<Shaders> Create();

        virtual ~Shaders() = default;

        virtual Shader* createFromFile(const std::filesystem::path& filepath) = 0;
        virtual Shader* get(uint32_t id) = 0;
        virtual std::unique_ptr<Shader> extract(uint32_t id) = 0;
    };
};
