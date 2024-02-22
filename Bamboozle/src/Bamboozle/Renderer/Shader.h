#pragma once

namespace bbzl
{
    using ShaderData = std::vector<std::byte>;

    class Shader
    {
    public:
        enum Type
        {
            Vertex,
            Pixel,

            Count
        };

    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void bindUniformBlock(const char* blockName, uint32_t bindPoint) const = 0;
        virtual void setSampler(const char* sampler, uint32_t value) const = 0;

        virtual const char* getName() const = 0;
    };

} // namespace bbzl
