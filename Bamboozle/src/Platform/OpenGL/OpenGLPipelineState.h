#pragma once

#include "Bamboozle/Renderer/PipelineState.h"

// TODO: implement OpenGLPipelineState

namespace bbzl
{
    class OpenGLPipelineState : public PipelineState
    {
    public:
        void validate() override;
        void bind() override;
    private:
    };
}