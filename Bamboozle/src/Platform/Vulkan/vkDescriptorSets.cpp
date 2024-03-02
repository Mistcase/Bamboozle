#include "Bamboozle/bbzlpch.h"
#include "vkDescriptorSets.h"

#include "VKCall.h"
#include "vkDescriptorPool.h"
#include "vkDevice.h"
#include "Bamboozle/ShaderPassTypes.h"
#include "Bamboozle/Renderer/ShaderPass.h"
#include "Bamboozle/Renderer/VertexLayout.h"

// Make this file auto generated

namespace
{
    constexpr VkDescriptorType BBZL_TO_VK_DESCRIPTOR_TYPES[] = {
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
    };

    // TODO: why cannot be constexpr?
    using bbzl_type_stage = bbzl::PSOLayoutElement::Stage;
    const std::unordered_map<bbzl_type_stage, uint32_t> BBZL_TO_VK_BINDING_USAGE_STAGE = {
        { bbzl_type_stage::VERTEX_SHADER, VK_SHADER_STAGE_VERTEX_BIT },
        { bbzl_type_stage::FRAGMENT_SHADER, VK_SHADER_STAGE_FRAGMENT_BIT }
    };

    using namespace bbzl;
    vkPSOLayout GetPSOLayout_PassCommon()
    {
        vkPSOLayout layout;
        layout.push_back({ 0, 1, PSOLayoutElement::Type::UNIFORM_BUFFER, PSOLayoutElement::Stage::ALL_INCLUSIVE });
        layout.push_back({ 1, 1, PSOLayoutElement::Type::SAMPLER, PSOLayoutElement::Stage::ALL_INCLUSIVE });

        return layout;
    }

    vkPSOLayout GetPSOLayout_PassTest()
    {
        return {};
    }

    vkPSOLayout GetPassPipelineLayout(bbzl::ShaderPassType type)
    {
        switch (type)
        {
        case ShaderPassType::PASS_COMMON:
            return GetPSOLayout_PassCommon();

        case ShaderPassType::PASS_TEST:
            return GetPSOLayout_PassTest();

        default:
            // ASSERT_FAIL("Not implemented");
            return {};
        }
    }
}

namespace bbzl
{
    vkDescriptorSetsManager::vkDescriptorSetsManager()
    {
        const auto passCount = static_cast<size_t>(ShaderPassType::COUNT);
        m_passSetsList.resize(passCount);
        for (size_t pass = 0; pass < passCount; ++pass)
        {
            auto& layout = m_passSetsList[pass];
            layout = GetPassPipelineLayout(ShaderPassType(pass));

            const auto descriptorCount = layout.size();
            if (descriptorCount == 0)
            {
                continue;
            }

            std::vector<VkDescriptorSetLayoutBinding> bindings(descriptorCount);
            for (size_t i = 0; i < descriptorCount; ++i)
            {
                const auto& binding = layout[i];
                auto& vkBinding = bindings[i];

                vkBinding.binding = binding.binding;
                vkBinding.descriptorCount = binding.countOfElements;
                vkBinding.descriptorType = BBZL_TO_VK_DESCRIPTOR_TYPES[static_cast<size_t>(binding.type)];
                vkBinding.pImmutableSamplers = nullptr;

                for (const auto [bbzlStage, vkStage] : BBZL_TO_VK_BINDING_USAGE_STAGE)
                {
                    if (binding.stageFlags & bbzlStage)
                    {
                        vkBinding.stageFlags |= vkStage;
                    }
                }
              }

            VkDescriptorSetLayoutCreateInfo layoutInfo{};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
            layoutInfo.pBindings = bindings.data();

            VK_CALL(vkCreateDescriptorSetLayout(getVkDeviceNative(), &layoutInfo, nullptr, &layout.layout));
        }
    }

    vkDescriptorSetsManager::~vkDescriptorSetsManager()
    {
        for (size_t pass = 0; pass < size_t(ShaderPassType::COUNT); ++pass)
        {
            const auto& set = m_passSetsList[size_t(pass)];
            vkDestroyDescriptorSetLayout(getVkDeviceNative(), set.layout, nullptr);   
        }
    }

    const vkPSOLayout& vkDescriptorSetsManager::getPSOLayout(ShaderPassType pass) const
    {
        return m_passSetsList[size_t(pass)];
    }
}
