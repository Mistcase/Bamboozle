#pragma once

#include <filesystem>

namespace bubble
{
    class Shader;

    class Shaders
    {
    public:
        static std::unique_ptr<Shaders> Create();

        virtual ~Shaders() = default;

        virtual Shader* createFromFile(std::filesystem::path filepath) = 0;
        virtual Shader* get(uint32_t hash) = 0;
    };
};
