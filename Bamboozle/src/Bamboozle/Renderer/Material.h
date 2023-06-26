#pragma once

#include "Bamboozle/Core.h"
#include <filesystem>
#include <vector>

namespace bbzl
{
    class Texture;
    class Shader;
    class UniformBuffer;

    class MaterialComponent
    {
    public:
        struct LightingParams
        {
            float kAmbient;
            float kDiffuse;
            float kSpecular;
            float shininess;
        };

        using Textures = std::vector<Ref<Texture>>;
        MaterialComponent(Shader* shader, const LightingParams& params, Textures&& textures);

        void apply() const;

    private:
        Textures m_textures;
        Shader* m_shader;

        Ref<UniformBuffer> m_uniformBuffer;

    private:
        enum class MaterialTextureType
        {
            Default,
            SpecularMap,

            Count
        };

        struct MaterialBuffer
        {
            float ka;
            float kd;
            float ks;
            float sa;

            int textureDefault;
            int textureSpecularMap;
        };
        MaterialBuffer m_uniformBufferData;
    };

} // namespace bbzl
