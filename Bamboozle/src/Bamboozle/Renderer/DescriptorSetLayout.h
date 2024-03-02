#pragma once
#include <vulkan/vulkan_core.h>

namespace bbzl
{
    struct PSOLayoutElement
    {
        enum class Type
        {
            UNIFORM_BUFFER,
            SAMPLER,

            COUNT
        };

        enum Stage : uint32_t
        {
            VERTEX_SHADER = 1,
            FRAGMENT_SHADER = 1 << 1,

            ALL_INCLUSIVE = VERTEX_SHADER | FRAGMENT_SHADER
        };

        /*----------Content----------*/
        uint32_t binding;
        uint32_t countOfElements; // > 1, if array
        Type type;
        uint32_t stageFlags;
    };

    struct vkPSOLayout : std::vector<PSOLayoutElement>
    {
        VkDescriptorSetLayout layout = VK_NULL_HANDLE;
    };

}
