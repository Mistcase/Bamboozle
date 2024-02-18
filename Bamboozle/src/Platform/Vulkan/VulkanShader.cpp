#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "VulkanShader.h"

namespace bbzl
{
    VulkanShader::VulkanShader(const std::string& name)
        : m_name(name)
    {
        
    }

    VulkanShader::~VulkanShader()
    {
       
    }

    void VulkanShader::bind() const
    {
       
    }

    void VulkanShader::unbind() const
    {
        
    }

    void VulkanShader::bindUniformBlock(const char* blockName, uint32_t bindPoint) const
    {
       
    }

    void VulkanShader::setSampler(const char* sampler, uint32_t value) const
    {
        
    }

    // void VulkanShader::submitUniformBuffer(, const void* data, size_t size) const
    // {
    // 	// Send data to shader
    // 	static_assert(false);
    // }

    const char* VulkanShader::getName() const
    {
        return m_name.c_str();
    }

} // namespace bbzl
