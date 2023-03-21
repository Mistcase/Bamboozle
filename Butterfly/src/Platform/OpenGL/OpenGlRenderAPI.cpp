#include "Butterfly/butterflypch.h"
#include "OpenGLRenderAPI.h"

#include "Butterfly/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace butterfly
{
    void OpenGLRenderAPI::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
		// glDisable(GL_CULL_FACE);
    }

    void OpenGLRenderAPI::setViewport(uint32_t left, uint32_t bottom, uint32_t width, uint32_t height)
    {
        glViewport(left, bottom, width, height);
    }

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, (GLsizei)(vertexArray->getIndexBuffer()->getCount()), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray, size_t count)
    {
        glDrawElements(GL_TRIANGLES, (GLuint)count, GL_UNSIGNED_INT, nullptr);
    }

} // namespace butterfly
