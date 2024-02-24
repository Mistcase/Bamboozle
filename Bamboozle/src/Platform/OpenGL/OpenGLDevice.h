#pragma once

#include "Bamboozle/Renderer/Device.h"

namespace bbzl
{
    class OpenGLContext;
    struct PipelineState;

    class OpenGLDevice : public VidDeviceInterface
    {
    public:
        OpenGLDevice();
        ~OpenGLDevice();

        // Not copyable or movable
        OpenGLDevice(const OpenGLDevice&) = delete;
        void operator=(const OpenGLDevice&) = delete;
        OpenGLDevice(OpenGLDevice&&) = delete;
        OpenGLDevice& operator=(OpenGLDevice&&) = delete;

        void swapBuffers() override;

        void beginFrame() override {}
        void endFrame() override {}

        PipelineState* createPipelineStateObject() override;
        void destroyPipelineStateObject(PipelineState* pso) override;

        Shader* createShader(Shader::Type type, const ShaderData& data) override;
        void destroyShader(Shader* shader) override;

    private:
        std::unique_ptr<OpenGLContext> m_context;
    };

} // namespace bbzl
