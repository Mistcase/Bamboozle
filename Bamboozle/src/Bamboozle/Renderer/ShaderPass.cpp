#include "Bamboozle/bbzlpch.h"
#include "ShaderPass.h"

namespace bbzl
{
    ShaderPass::~ShaderPass()
    {
        g_RenderDevice->destroyPipelineStateObject(m_pso);
    }

    ShaderPass::ShaderPass() = default;

}