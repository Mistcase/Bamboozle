#pragma once

#include "Shader.h"
#include "VertexLayout.h"
#include "Bamboozle/ShaderPassTypes.h"

namespace bbzl
{
    struct PipelineState
    {
        struct RenderState
        {
            bool z_write = true;
            bool z_test = true;
        };

        enum class PrimitiveTopologyType
        {
            Triangles,
            TriangleStrip,
            Lines,
            LineStrip, // Does Vulkan support it?

            Count
        };

        using ShaderBundle = std::array<Shader*, Shader::Type::Count>;

        // Data
        ShaderBundle shaderBundle{};
        PrimitiveTopologyType primTopologyType = PrimitiveTopologyType::Triangles;
        VertexLayout vertexLayout;
        ShaderPassType passId = ShaderPassType::COUNT;

        /*Deleting a pointer to a derived type through the base pointer is technically UB when the destructor of the base class is not virtual.
        Quoting from the C++ standard 5.3.5/3 */
        virtual ~PipelineState() = default;
        virtual void validate() = 0;

        virtual void bind() = 0;
    };

} // namespace
