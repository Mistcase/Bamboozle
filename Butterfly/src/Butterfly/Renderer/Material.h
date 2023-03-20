#pragma once

#include "Butterfly/Core.h"

namespace butterfly
{
    class Texture;

    struct Material
    {
    public:
        Ref<Texture> texture;

        float kAmbient;
        float kDiffuse;
        float kSpecular;
        float shininess;
    };

} // namespace butterfly
