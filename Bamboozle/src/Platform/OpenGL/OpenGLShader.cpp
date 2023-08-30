#include "OpenGLShader.h"

#include "Bamboozle/Log.h"
#include "Bamboozle/bbzl.h"
#include "GlCall.h"

#include <glm/gtc/type_ptr.hpp>

namespace bbzl
{
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& srcVertex, const std::string& srcFragment)
        : m_name(name)
    {
        auto compileShader = [](GLenum type, const std::string& name, const std::string& src) {
            GLuint shader;
			GL_CALL(shader = glCreateShader(type));

            const GLchar* source = src.c_str();
            GL_CALL(glShaderSource(shader, 1, &source, 0));
			GL_CALL(glCompileShader(shader));

            GLint isCompiled = 0;
            GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled));
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength));

                std::vector<GLchar> infoLog(maxLength);
                GL_CALL(glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]));

				GL_CALL(glDeleteShader(shader));

                BBZL_CORE_ERROR("Shader {0} compilation failed!", name);
                BBZL_CORE_ERROR("{0}\n\n", infoLog.data());
            }

            return shader;
        };

        auto vertexShader = compileShader(GL_VERTEX_SHADER, name, srcVertex);
        auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, name, srcFragment);

        GL_CALL(m_rendererId = glCreateProgram());

        if (!vertexShader || !fragmentShader)
        {
            GL_CALL(glDeleteProgram(m_rendererId));
            GL_CALL(glDeleteShader(vertexShader));
            GL_CALL(glDeleteShader(fragmentShader));
            return;
        }

        GL_CALL(glAttachShader(m_rendererId, vertexShader));
		GL_CALL(glAttachShader(m_rendererId, fragmentShader));
		GL_CALL(glLinkProgram(m_rendererId));

        GLint isLinked = 0;
        GL_CALL(glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int*)&isLinked));
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            GL_CALL(glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength));

            std::vector<GLchar> infoLog(maxLength);
            GL_CALL(glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]));

            GL_CALL(glDeleteProgram(m_rendererId));
			GL_CALL(glDeleteShader(vertexShader));
			GL_CALL(glDeleteShader(fragmentShader));

            BBZL_CORE_ERROR("Shader \"{0}\" link error", name);
            BBZL_CORE_ERROR("{0}\n\n", infoLog.data());
        }

        // Always detach shaders after a successful link.
        GL_CALL(glDetachShader(m_rendererId, vertexShader));
        GL_CALL(glDetachShader(m_rendererId, fragmentShader));

        m_isAssembled = true;
    }

    OpenGLShader::~OpenGLShader()
    {
        GL_CALL(glUseProgram(0));
        GL_CALL(glDeleteProgram(m_rendererId));
    }

    void OpenGLShader::bind() const
    {
        GL_CALL(glUseProgram(m_rendererId));
    }

    void OpenGLShader::unbind() const
    {
        GL_CALL(glUseProgram(0));
    }

    void OpenGLShader::bindUniformBlock(const char* blockName, uint32_t bindPoint) const
    {
        GLuint index;
		GL_CALL(index = glGetUniformBlockIndex(m_rendererId, blockName));
        GL_CALL(glUniformBlockBinding(m_rendererId, index, bindPoint));
    }

    void OpenGLShader::setSampler(const char* sampler, uint32_t value) const
    {
        GL_CALL(setUniform1i(sampler, value));
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
		GLint location;
		GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
        BBZL_CORE_ASSERT(location != -1, "Uniform is not found");

        GL_CALL(glUniform1i(location, i));
    }

    void OpenGLShader::setUniform1f(const std::string& name, float value) const
    {
        // TODO: make uniform location cache
		GLint location;
        GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
        BBZL_CORE_ASSERT(location != -1, "Uniform is not found");

        GL_CALL(glUniform1f(location, value));
    }

    void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& data) const
    {
        // TODO: make uniform location cache
		GLint location;
        GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
        BBZL_CORE_ASSERT(location != -1, "Uniform is not found");

        GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data)));
    }

    void OpenGLShader::setUniform3f(const std::string& name, const glm::vec3& data) const
    {
        // TODO: make uniform location cache
		GLint location;
        GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
        BBZL_CORE_ASSERT(location != -1, "Uniform is not found");

        GL_CALL(glUniform3f(location, data.r, data.g, data.b));
    }

    void OpenGLShader::setUniform4f(const std::string& name, const glm::vec4& data) const
    {
		// TODO: make uniform location cache

		GLint location;
        GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
        BBZL_CORE_ASSERT(location != -1, "Uniform is not found");

        GL_CALL(glUniform4f(location, data.r, data.g, data.b, data.a));
    }

    void OpenGLShader::setUniformIntArray(const std::string& name, const int* data, uint32_t count) const
    {
        // TODO: make uniform location cache
        GLint location;
		GL_CALL(location = glGetUniformLocation(m_rendererId, name.c_str()));
        BBZL_CORE_ASSERT(location != -1, "Uniform is not found");

        GL_CALL(glUniform1iv(location, count, data));
    }

} // namespace bbzl
