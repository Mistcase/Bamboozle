#pragma once

#include "Bamboozle/Renderer/Shader.h"

namespace bbzl
{
    struct PipelineState;
    // class ShaderCompiler;

    class VidDeviceInterface
    {
    public:
        VidDeviceInterface() = default;
        virtual ~VidDeviceInterface() = default;

        // Not copyable or movable
        VidDeviceInterface(const VidDeviceInterface&) = delete;
        void operator=(const VidDeviceInterface&) = delete;
        VidDeviceInterface(VidDeviceInterface&&) = delete;
        VidDeviceInterface& operator=(VidDeviceInterface&&) = delete;

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

    private:
    };

} // namespace bbzl