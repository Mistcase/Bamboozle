#pragma once

#include "Butterfly/Renderer/GraphicsContext.h"
#include "Butterfly/Window.h"

struct GLFWwindow;

namespace butterfly
{
    class WindowImpl : public Window
    {
    public:
        WindowImpl(const WindowProps& props);
        virtual ~WindowImpl();

        void onUpdate() override;

        inline unsigned int getWidth() const override
        {
            return m_data.width;
        }
        inline unsigned int getHeight() const override
        {
            return m_data.height;
        }

        inline void setEventCallback(const FnEventCallback& callback) override
        {
            m_data.eventCallback = callback;
        }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

        void* getNativeWindow() const override;

    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

    private:
        GLFWwindow* m_window;
        GraphicsContext* m_context;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vSync;

            FnEventCallback eventCallback;
        };

        WindowData m_data;
    };

} // namespace butterfly
