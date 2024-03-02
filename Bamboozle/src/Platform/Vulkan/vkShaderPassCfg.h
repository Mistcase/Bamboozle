#pragma once

#include "Bamboozle/Renderer/ShaderPassConfig.h"

#include "vkDescriptorPool.h"
#include "vkPipelineState.h"
#include <vulkan/vulkan_core.h>

namespace bbzl
{
    class vkShaderPassCfg : public ShaderPassCfg
    {
    public:
        vkShaderPassCfg();

        // Only one descriptor st is supported for now
        void setupPass(const VertexLayout& format, ShaderPassType type) override;

    private:
        vkPipelineState m_pso;
    };

}
