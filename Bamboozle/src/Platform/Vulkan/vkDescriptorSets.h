#pragma once

#include "Bamboozle/ShaderPassTypes.h"
#include "Bamboozle/Renderer/DescriptorSetLayout.h"

namespace bbzl
{
    class vkDescriptorSetsManager final
    {
    public:
        vkDescriptorSetsManager();
        ~vkDescriptorSetsManager();

        const vkPSOLayout& getPSOLayout(ShaderPassType pass) const;

    private:
        std::vector<vkPSOLayout> m_passSetsList;
    };
}
