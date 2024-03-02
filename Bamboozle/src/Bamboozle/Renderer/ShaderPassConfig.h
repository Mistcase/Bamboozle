#pragma once

#include "Bamboozle/ShaderPassTypes.h"

namespace bbzl
{
    class VertexLayout;
    class PSOLayout;

    class ShaderPassCfg
    {
    public:
        virtual ~ShaderPassCfg() = default;
        ShaderPassCfg(const ShaderPassCfg&) = delete;
        ShaderPassCfg(ShaderPassCfg&&) = delete;
        ShaderPassCfg& operator=(const ShaderPassCfg&) = delete;
        ShaderPassCfg& operator=(ShaderPassCfg&&) = delete;

        // Only one descriptor set is supported for now
        virtual void setupPass(const VertexLayout& format, ShaderPassType type) = 0;

    protected:
        ShaderPassCfg() = default;
    };
    
}
