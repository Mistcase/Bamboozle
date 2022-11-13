#include "bubblepch.h"
#include "OpenGLRenderAPI.h"

#include "Bubble/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace bubble
{
    void OpenGLRenderAPI::init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.r, color.b, color.a);
    }

    void OpenGLRenderAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, (GLsizei)(vertexArray->getIndexBuffer()->getCount()), GL_UNSIGNED_INT, nullptr);
    }

} // namespace bubble
