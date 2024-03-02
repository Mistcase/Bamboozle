#pragma once

#include "Device.h"
#include "DeviceFwd.h"
#include "VertexLayout.h"

namespace bbzl
{
    struct PipelineState;

    // Passes can be different from rendering system side: SKY, TERRAIN, VFX, UI
    class ShaderPass
    {
    public:
        virtual ~ShaderPass();

        ShaderPass(const ShaderPass&) = delete;
        ShaderPass(ShaderPass&&) = delete;
        ShaderPass& operator=(const ShaderPass&) = delete;
        ShaderPass& operator=(ShaderPass&&) = delete;

        virtual void prepare() = 0;

        ShaderPass();
    protected:
        

    protected:
        // May be layout can be changed and cached later. So store it as field.
        VertexLayout m_vboLayout;
        PipelineState* m_pso = nullptr;
    };

}
