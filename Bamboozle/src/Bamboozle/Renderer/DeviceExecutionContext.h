#pragma once

namespace bbzl
{
    class DeviceExecutionContextInterface
    {
    public:
        virtual ~DeviceExecutionContextInterface() = default;

        virtual void beginFrame() {}
        virtual void endFrame() {}

        virtual void beginRenderPass() {}
        virtual void endRenderPass() {}

        virtual void getBackbuffer() {}
    };
}
