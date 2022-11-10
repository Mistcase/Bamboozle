#pragma once

namespace bubble
{
    enum class RendererAPI
    {
        None,
        OpenGL
    };

    class Renderer
    {
    public:
        static inline RendererAPI GetAPI()
        {
            return m_rendererAPI;
        }

        static RendererAPI m_rendererAPI;
    };

} // namespace bubble
