#include "OpenGLRenderAPI.h"

#include "Bamboozle/Renderer/VertexArray.h"
#include "Bamboozle/bbzl.h"
#include "GlCall.h"

namespace bbzl
{
    void OpenGLRenderAPI::init()
    {
        // Reset global state
        m_renderAPI = RenderAPI::API::OpenGL;

        GL_CALL(glEnable(GL_BLEND));
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        GL_CALL(glEnable(GL_DEPTH_TEST));
        // GL_CALL(glDisable(GL_CULL_FACE));
    }
    void OpenGLRenderAPI::setPointSize(float size)
    {
        GL_CALL(glPointSize(size));
    }

    void OpenGLRenderAPI::setViewport(uint32_t left, uint32_t bottom, uint32_t width, uint32_t height)
    {
        GL_CALL(glViewport(left, bottom, width, height));
    }

    void OpenGLRenderAPI::setLineWidth(float width)
    {
        GL_CALL(glLineWidth(width));
    }

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
    }

    void OpenGLRenderAPI::clear()
    {
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void OpenGLRenderAPI::drawPoints(Ref<VertexArray> vertexArray, size_t count)
    {
        GL_CALL(glDrawArrays(GL_POINTS, 0, count));
    }

    void OpenGLRenderAPI::drawLines(Ref<VertexArray> vertexArray, size_t count)
    {
        GL_CALL(glDrawArrays(GL_LINES, 0, count));
    }

    void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
    {
        GL_CALL(glDrawElements(GL_TRIANGLES, (GLsizei)(vertexArray->getIndexBuffer()->getCount()), GL_UNSIGNED_INT, nullptr));
    }

    void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray, size_t count)
    {
        GL_CALL(glDrawElements(GL_TRIANGLES, (GLuint)count, GL_UNSIGNED_INT, nullptr));
    }

} // namespace bbzl
