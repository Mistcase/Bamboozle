#pragma once

#include <string>
#include <glm/glm.hpp>

namespace bubble
{
    class Shader
    {
    public:
        Shader(const std::string& srcVertex, const std::string& srcFragment);;
        ~Shader();

        void bind() const;
        void unbind() const;

        void setUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        uint32_t m_rendererId;
    };

} // namespace bubble
