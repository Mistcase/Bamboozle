#pragma once

#include "Bubble/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace bubble
{
    class OpenGLShader : public Shader
    {
    public:
        ~OpenGLShader() override;

        void bind() const override;
        void unbind() const override;

        const char* getName() const override;

        void setUniform1i(const std::string name, int i) const;
        void setUniformMat4(const std::string& name, const glm::mat4& data) const;
        void setUniform4f(const std::string& name, const glm::vec4& data) const;

    private:
        OpenGLShader(const std::string& name, const std::string& srcVertex, const std::string& srcFragment);
        friend class OpenGLShaders;

    private:
        bool m_isAssembled = false;

    private:
        const std::string m_name;
        uint32_t m_rendererId;
    };

} // namespace bubble
