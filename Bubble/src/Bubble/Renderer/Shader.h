#pragma once

#include <string>
#include <glm/glm.hpp>

namespace bubble
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Shader* Create(const std::string& srcVertex, const std::string& srcFragment);
    private:
        uint32_t m_rendererId;
    };

} // namespace bubble
