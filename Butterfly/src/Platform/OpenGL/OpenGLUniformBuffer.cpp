#include "Butterfly/butterflypch.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace butterfly
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size)
	{
		glGenBuffers(1, &m_rendererId);
		glBindBuffer(GL_UNIFORM_BUFFER, m_rendererId);
		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	}

	void OpenGLUniformBuffer::bind(uint32_t bindPoint) const
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, bindPoint, m_rendererId);
	}

	void OpenGLUniformBuffer::bind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_rendererId);
	}

	void OpenGLUniformBuffer::unbind() const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::submit(const void* data, size_t size) const
	{
		assert(data != nullptr);
		glBindBuffer(GL_UNIFORM_BUFFER, m_rendererId);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	}

} // namespace butterfly
