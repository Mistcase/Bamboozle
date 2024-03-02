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
        VkShaderModule* getNativeModulePtr() { return &m_nativeModule; }

    private:
        // Already precompileed shaders expected (SPIR-V)
        VulkanShader(const std::string& name);
        friend class VulkanShaders;
        friend class vkDevice;

    private:
        const std::string m_name;
        VkShaderModule m_nativeModule;
    };

} // namespace bbzl
