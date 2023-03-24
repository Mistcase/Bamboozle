#pragma once

#include "Butterfly/Core.h"
#include <glm/glm.hpp>
#include <memory>

namespace butterfly
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
        inline static API GetAPI()
        {
            return m_renderAPI;
        };

        virtual void init() = 0;

        virtual void setViewport(uint32_t left, uint32_t bottom, uint32_t width, uint32_t height) = 0;
        virtual void setLineWidth(float width) = 0;

        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;

        virtual void drawLines(Ref<VertexArray> vertexArray, size_t count) = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;
        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, size_t count) = 0;

    private:
        static API m_renderAPI;
    };

} // namespace butterfly
