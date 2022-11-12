#include "bubblepch.h"
#include "OpenGLShader.h"

#include "Bubble/Log.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace bubble
{
    OpenGLShader::OpenGLShader(const std::string& srcVertex, const std::string& srcFragment)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar *source = srcVertex.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            BUBBLE_CORE_ERROR("{0}", infoLog.data());
            BUBBLE_CORE_ASSERT(false, "Vertex shader compilation failure!");
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = (const GLchar *)srcFragment.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            BUBBLE_CORE_ERROR("{0}", infoLog.data());
            BUBBLE_CORE_ASSERT(false, "Fragment shader compilation failure!");
        }

        m_rendererId = glCreateProgram();

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

            BUBBLE_CORE_ERROR("{0}", infoLog.data());
            BUBBLE_CORE_ASSERT(false, "Shader link failure!");
        }

        // Always detach shaders after a successful link.
        glDetachShader(m_rendererId, vertexShader);
        glDetachShader(m_rendererId, fragmentShader);
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

    void OpenGLShader::setUniformMat4(const std::string& name, const glm::mat4& data) const
    {
        // TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUBBLE_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data ));
    }

    void OpenGLShader::setUniform4f(const std::string& name, const glm::vec4& data) const
    {
        // TODO: make uniform location cache
        auto location = glGetUniformLocation(m_rendererId, name.c_str());
        BUBBLE_CORE_ASSERT(location != -1, "Uniform is not found");

        glUniform4f(location, data.r, data.g, data.b, data.a);
    }

} // namespace bubble
