#include "Bamboozle/bbzlpch.h"
#include "VulkanRenderAPI.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/Renderer/VertexArray.h"

// Create Device

namespace bbzl
{
    VulkanRenderAPI::VulkanRenderAPI()
    {
    }

    void VulkanRenderAPI::init()
    {
        // TODO: think about it
        // Reset global state
        m_renderAPI = API::Vulkan;

        m_device = std::make_unique<VulkanDevice>(Application::GetInstance().getWindow());
    }

    void VulkanRenderAPI::setPointSize(float size)
    {
    }

    void VulkanRenderAPI::setViewport(uint32_t left, uint32_t bottom, uint32_t width, uint32_t height)
    {
    }

    void VulkanRenderAPI::setLineWidth(float width)
    {
    }

    void VulkanRenderAPI::setClearColor(const glm::vec4& color)
    {
    }

    void VulkanRenderAPI::clear()
    {
        const volatile int a = 10;
    }

    void VulkanRenderAPI::drawPoints(Ref<VertexArray> vertexArray, size_t count)
    {
    }

    void VulkanRenderAPI::drawLines(Ref<VertexArray> vertexArray, size_t count)
    {
    }

    void VulkanRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
    {
        const volatile int a = 10;
    }

    void VulkanRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray, size_t count)
    {
        const volatile int a = 10;
    }

} // namespace bbzl
