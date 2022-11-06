#pragma once

#include <string>

namespace bubble
{
    class Shader
    {
    public:
        Shader(const std::string& srcVertex, const std::string& srcFragment);;
        ~Shader();

        void bind() const;
        void unbind() const;

    private:
        uint32_t m_rendererId;
    };

} // namespace bubble
