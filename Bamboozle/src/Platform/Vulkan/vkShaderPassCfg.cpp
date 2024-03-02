#include "Bamboozle/bbzlpch.h"
#include "vkShaderPassCfg.h"

#include "VulkanContext.h"
#include "vkDevice.h"

#include "Bamboozle/Renderer/DescriptorSetLayout.h"

#include "vkDescriptorPool.h"
#include "vkExecutionContext.h"


namespace bbzl
{
    vkShaderPassCfg::vkShaderPassCfg()
        : m_pso(*getVkDevice())
    {
    }

    void vkShaderPassCfg::setupPass(const VertexLayout& format, ShaderPassType type)
    {
        
    }
}
