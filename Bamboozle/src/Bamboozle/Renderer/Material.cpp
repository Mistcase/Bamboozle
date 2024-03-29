#include "Material.h"

#include "Bamboozle/Hash.h"
#include "Bamboozle/Renderer/Shader.h"
#include "Bamboozle/Renderer/Texture.h"
#include "Bamboozle/Renderer/UniformBuffer.h"
#include "Bamboozle/bbzl.h"

namespace bbzl
{
    MaterialComponent::MaterialComponent(Shader* shader, const LightingParams& params, Textures&& textures)
        : m_shader(shader)
        , m_textures(std::move(textures)) // Clang warning?
        , m_uniformBuffer(UniformBuffer::Create(sizeof(MaterialBuffer)))
    {
        assert(m_textures.size() <= static_cast<size_t>(MaterialTextureType::Count));

        // Fill uniform buffer
        m_uniformBufferData.ka = params.kAmbient;
        m_uniformBufferData.kd = params.kDiffuse;
        m_uniformBufferData.ks = params.kSpecular;
        m_uniformBufferData.sa = params.shininess;

        const auto idxDefautTexture = static_cast<size_t>(MaterialTextureType::Default);
        m_uniformBufferData.textureDefault = m_textures.size() > idxDefautTexture ? idxDefautTexture : -1;

        const auto idxSpecularMap = static_cast<size_t>(MaterialTextureType::SpecularMap);
        m_uniformBufferData.textureSpecularMap = m_textures.size() > idxSpecularMap ? idxSpecularMap : -1;

        m_shader->bind();
        m_shader->bindUniformBlock("Material", 1);
    }

    void MaterialComponent::apply() const
    {
        m_shader->bind();
        m_uniformBuffer->bind(1);
        m_uniformBuffer->submit(&m_uniformBufferData, sizeof(m_uniformBufferData));

        assert(m_textures.size() <= static_cast<size_t>(MaterialTextureType::Count));
        for (size_t i = 0, size = m_textures.size(); i < size; i++)
        {
            m_shader->setSampler(("u_Textures[" + std::to_string(i) + "]").c_str(), i); // TODO: FIXME PLEASE
            m_textures[i]->bind(i);
        }
    }

} // namespace bbzl
