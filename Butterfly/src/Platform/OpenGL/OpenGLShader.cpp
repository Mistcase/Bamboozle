#include "Butterfly/butterflypch.h"
#include "OpenGLShader.h"

#include "Butterfly/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace butterfly
{
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& srcVertex, const std::string& srcFragment)
        : m_name(name)
    {
        auto compileShader = [](GLenum type, const std::string& name, const std::string& src)
        {
            GLuint shader = glCreateShader(type);
            const GLchar *source = src.c_str();
            glShaderSource(shader, 1, &source, 0);
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                BUTTERFLY_CORE_ERROR("Shader {0} compilation failed!", name);
                BUTTERFLY_CORE_ERROR("{0}\n\n", infoLog.data());
            }

            return shader;
        };

        auto vertexShader = compileShader(GL_VERTEX_SHADER, name, srcVertex);
        auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, name, srcFragment);
        m_rendererId = glCreateProgram();

        if (!vertexShader || !fragmentShader)
        {
            glDeleteProgram(m_rendererId);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return;
        }

        glAttachShader(m_rendererId, vertexShader);
        glAttachShader(m_rendererId, fragmentShader);
        glLinkProgram(m_rendererId);

        GLint isLinked = 0;
        glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_rendererId);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            BUTTERFLY_CORE_ERROR("Shader \"{0}\" link error", name);
            BUTTERFLY_CORE_ERROR("{0}\n\n", infoLog.data());
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_rendererId, vertexShader);
        glDetachShader(m_rendererId, fragmentShader);

        m_isAssembled = true;
    }

    OpenGLShader::~OpenGLShader()
    {
        glUseProgram(0);
        glDeleteProgram(m_rendererId);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(m_rendererId);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

	void OpenGLShader::bindUniformBlock(const char* blockName, uint32_t bindPoint) const
	{
		const auto index = glGetUniformBlockIndex(m_rendererId, blockName);
		glUniformBlockBinding(m_rendererId, index, bindPoint);
	}

	void OpenGLShader::setSampler(const char* sampler, uint32_t value) const
	{
		setUniform1i(sampler, value);
	}

	// void OpenGLShader::submitUniformBuffer(, const void* data, size_t size) const
	// {
	// 	// Send data to shader
	// 	static_assert(false);
	// }

    const char* OpenGLShader::getName() const
    {
        return m_name.c_str();
    }

    void OpenGLShader::setUniform1i(const std::string& name, int i) const
    {
        // TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUTTERFLY_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniform1i(location, i);
    }

	void OpenGLShader::setUniform1f(const std::string& name, float value) const
	{
		// TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUTTERFLY_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniform1f(location, value);
	}

    void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& data) const
    {
        // TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUTTERFLY_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
    }

	void OpenGLShader::setUniform3f(const std::string& name, const glm::vec3& data) const
	{
		// TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUTTERFLY_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniform3f(location, data.r, data.g, data.b);
	}

    void OpenGLShader::setUniform4f(const std::string& name, const glm::vec4& data) const
    {
        // TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUTTERFLY_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniform4f(location, data.r, data.g, data.b, data.a);
    }

    void OpenGLShader::setUniformIntArray(const std::string& name, const int* data, uint32_t count) const
    {
        // TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUTTERFLY_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniform1iv(location, count, data);
    }

} // namespace butterfly
