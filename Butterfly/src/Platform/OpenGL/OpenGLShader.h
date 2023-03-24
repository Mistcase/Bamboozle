#pragma once

#include "Butterfly/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace butterfly
{
    class OpenGLShader : public Shader
    {
    public:
        ~OpenGLShader() override;

        void bind() const override;
        void unbind() const override;

		void bindUniformBlock(const char* blockName, uint32_t bindPoint) const override;
		void setSampler(const char* sampler, uint32_t value) const override;

        const char* getName() const override;

		// TODO: Remove it finally
        void setUniform1i(const std::string& name, int i) const;
		void setUniform1f(const std::string& name, float value) const;
        void setUniformMat4(const std::string& name, const glm::mat4& data) const;
		void setUniform3f(const std::string& name, const glm::vec3& data) const;
        void setUniform4f(const std::string& name, const glm::vec4& data) const;
        void setUniformIntArray(const std::string& name, const int* data, uint32_t count) const;

    private:
        OpenGLShader(const std::string& name, const std::string& srcVertex, const std::string& srcFragment);
        friend class OpenGLShaders;

    private:
        bool m_isAssembled = false;

    private:
        const std::string m_name;
        uint32_t m_rendererId;
    };

} // namespace butterfly
