#pragma once

#include "Bamboozle/Renderer/ShaderPass.h"

namespace bbzl
{
    class ShaderPassCommon : public ShaderPass
    {
    public:
        ShaderPassCommon();
        ~ShaderPassCommon();

        void prepare() override;
    };
}
