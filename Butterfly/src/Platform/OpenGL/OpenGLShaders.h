#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Renderer/Shaders.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <unordered_map>

namespace butterfly
{
    class OpenGLShader;

    class OpenGLShaders : public Shaders
    {
    public:
        ~OpenGLShaders() override;

        Shader* createFromFile(const std::filesystem::path& filepath) override;
        Shader* get(uint32_t id) override;
        std::unique_ptr<Shader> extract(uint32_t id) override;

    private:
        using SourcePair = std::pair<std::string, std::string>;

        std::string loadSource(const std::filesystem::path& filepath) const;
        SourcePair preprocess(const std::string& source) const;
        OpenGLShader* build(const std::string& name, const SourcePair& sources);

    private:
        using Container = std::unordered_map<uint32_t, std::unique_ptr<OpenGLShader>>;
        Container m_shaders;
    };

} // namespace butterfly
