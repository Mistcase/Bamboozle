#include "Bamboozle/bbzlpch.h"
#include "OpenGLDevice.h"

#include "OpenGLPipelineState.h"
#include "OpenGLContext.h"
#include "Bamboozle/Application.h"

namespace bbzl
{
    OpenGLDevice::OpenGLDevice()
    {
        const auto& glfwWindow = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
        m_context = std::make_unique<OpenGLContext>(glfwWindow);
    }

    OpenGLDevice::~OpenGLDevice()
    {
        
    }

    void OpenGLDevice::swapBuffers()
    {
        m_context->swapBuffers();
    }

    PipelineState* OpenGLDevice::createPipelineStateObject()
    {
        return new OpenGLPipelineState();
    }

    void OpenGLDevice::destroyPipelineStateObject(PipelineState* pso)
    {
        delete pso;
    }

    Shader* OpenGLDevice::createShader(Shader::Type type, const ShaderData& data)
    {
        ASSERT_FAIL("Not implemented");
        return nullptr;
    }

    void OpenGLDevice::destroyShader(Shader* shader)
    {
        delete shader;
    }
} // namespace bbzl
