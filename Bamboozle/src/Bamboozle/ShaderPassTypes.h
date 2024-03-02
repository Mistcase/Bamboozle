#pragma once

namespace bbzl
{
    enum class ShaderPassType
    {
        PASS_FIRST,

        PASS_COMMON = PASS_FIRST,
        PASS_TEST,
        PASS_SKY,
        PASS_UI,

        COUNT
    };
}