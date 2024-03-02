#pragma once

namespace bbzl
{
    class Texture2D;
    struct PipelineState;

    class DeviceExecutionContext
    {
    public:
        virtual ~DeviceExecutionContext() = default;

        virtual void setPSO(const PipelineState& pipeline) {}

        virtual void beginFrame() {}
        virtual void endFrame() {}

        virtual void beginRenderPass() {}
        virtual void endRenderPass() {}

        virtual void draw(size_t vertexCount, size_t instanceCount)
        {
            ASSERT_FAIL_NO_MSG();
        }
    };
}
