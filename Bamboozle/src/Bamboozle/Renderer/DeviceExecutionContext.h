#pragma once

namespace bbzl
{
    class Texture2D;
    struct PipelineState;

    class DeviceExecutionContextInterface
    {
    public:
        virtual ~DeviceExecutionContextInterface() = default;

        virtual void bindPipeline(const PipelineState& pipeline) {}

        virtual void beginFrame() {}
        virtual void endFrame() {}

        virtual void beginRenderPass() {}
        virtual void endRenderPass() {}

        virtual void getBackbuffer() {}

        virtual void testDraw(const PipelineState& pipeline, const Texture2D* texture)
        {
        }
    };
}
