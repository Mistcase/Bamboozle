#pragma once

#include "Bubble/Renderer/Shader.h"

namespace bubble
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& srcVertex, const std::string& srcFragment);
        ~OpenGLShader() override;

        void bind() const override;
        void unbind() const override;

        void setUniformMat4(const std::string& name, const glm::mat4& data) const;
        void setUniform4f(const std::string& name, const glm::vec4& data) const;

    private:
        uint32_t m_rendererId;
    };

} // namespace bubble
