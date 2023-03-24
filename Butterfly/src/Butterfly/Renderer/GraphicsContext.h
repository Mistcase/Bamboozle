#pragma once

namespace butterfly
{
    class GraphicsContext
    {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

} // namespace butterfly
