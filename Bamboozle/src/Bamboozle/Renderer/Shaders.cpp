#include "Shaders.h"

#include "Bamboozle/Assert.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShaders.h"
#include "Platform/Vulkan/vkDevice.h"
#include "Platform/Vulkan/VulkanShaders.h"

namespace bbzl
{
    std::unique_ptr<Shaders> Shaders::Create(RenderDevice* device)
    {
        const auto api = RenderAPI::GetAPI();
        switch (api)
        {
        case RenderAPI::API_TYPE::OpenGL:
            return std::make_unique<OpenGLShaders>();

        case RenderAPI::API_TYPE::Vulkan:
            return std::make_unique<VulkanShaders>(*(vkDevice*)(device));

        default:
            ASSERT_FAIL("Unknown API_TYPE");
            return nullptr;
        }
    }

} // namespace bbzl
