#pragma once

#include "Bamboozle/Renderer/Shader.h"

namespace bbzl
{
    struct PipelineState;
    // class ShaderCompiler;

    class RenderDevice
    {
    public:
        RenderDevice() = default;
        virtual ~RenderDevice() = default;

        // Not copyable or movable
        RenderDevice(const RenderDevice&) = delete;
        void operator=(const RenderDevice&) = delete;
        RenderDevice(RenderDevice&&) = delete;
        RenderDevice& operator=(RenderDevice&&) = delete;

        virtual void swapBuffers() = 0;

        virtual void beginFrame() = 0;
        virtual void endFrame() = 0;

        // Resource creation
        virtual PipelineState* createPipelineStateObject() = 0;
        virtual void destroyPipelineStateObject(PipelineState* pso) = 0;

        virtual Shader* createShader(Shader::Type type, const ShaderData& data) = 0;
        virtual void destroyShader(Shader* shader) = 0;

        /*virtual ShaderCompiler* createShaderCompiler() = 0;
        virtual void destroyShaderCompiler(ShaderCompiler) = 0;*/
    };

} // namespace bbzl