#include "RenderCommand.h"

#include "Bamboozle/bbzl.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"
#include "Platform/Vulkan/VulkanRenderAPI.h"

namespace bbzl
{
    void RenderCommand::Init(RenderAPI::API api)
    {
        if (api == RenderAPI::API::OpenGL)
        {
            m_renderAPI = std::make_unique<OpenGLRenderAPI>();
        }
        else if (api == RenderAPI::API::Vulkan)
        {
            m_renderAPI = std::make_unique<VulkanRenderAPI>();
        }
        else
        {
            ASSERT_FAIL("Unknown api");
        }

        m_renderAPI->init();
    }

    std::unique_ptr<RenderAPI> RenderCommand::m_renderAPI;
} // namespace bbzl
