#pragma once

#include "VulkanContext.h"
#include <glm/glm.hpp>

namespace bbzl
{
    struct SimplePushConstantData
    {
        glm::mat2 transform{ 1.0f };
        glm::vec2 offset{ 0.0f, 0.0f };
        alignas(16) glm::vec3 color{ 1.0f, 1.0f, 1.0f };
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoords;

        static std::vector<VkVertexInputBindingDescription> GetBindingDescriptions()
        {
            std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
            bindingDescriptions[0].binding = 0;
            bindingDescriptions[0].stride = sizeof(Vertex);
            bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // Or instance

            return bindingDescriptions;
        }

        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions()
        {
            std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = 0;

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoords);

            return attributeDescriptions;
        }
    };
}