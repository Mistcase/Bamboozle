#pragma once

#include "Bamboozle/Renderer/Shader.h"

namespace bbzl
{
    class VulkanShader : public Shader
    {
    public:
        ~VulkanShader() override;

        void bind() const override;
        void unbind() const override;

        void bindUniformBlock(const char* blockName, uint32_t bindPoint) const override;
        void setSampler(const char* sampler, uint32_t value) const override;

        const char* getName() const override;

        VkShaderModule getNativeModule() const { return m_nativeModule; }

    private:
        // Already precompileed shaders expected (SPIR-V)
        VulkanShader(const std::string& name, const std::string& srcVertex, const std::string& srcFragment);
        friend class VulkanShaders;

    private:
        bool m_isAssembled = false;

    private:
        const std::string m_name;
        uint32_t m_rendererId;

        VkShaderModule m_nativeModule;
    };

} // namespace bbzl
