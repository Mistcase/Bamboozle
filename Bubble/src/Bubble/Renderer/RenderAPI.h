#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace bubble
{
    class VertexArray;

    class RenderAPI
    {
    public:
        enum class API
        {
            None,
            OpenGL
        };

    public:
        inline static API GetAPI() { return m_renderAPI; };

        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

    private:
        static API m_renderAPI;
    };

} // namesapce bubble
