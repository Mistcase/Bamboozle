#pragma once

#include "Bamboozle/Renderer/GraphicsContext.h"
#include "Bamboozle/Window.h"

struct GLFWwindow;

namespace bbzl
{
    class WindowImpl : public Window
    {
    public:
        WindowImpl(const WindowProps& props);
        virtual ~WindowImpl();

        void createSurface(void* data) override;

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

		void setCursorVisible(bool visible) override;
        void setVSync(bool enabled) override;

        bool isVSync() const override;
		bool isCursorVisible() const override;

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
			bool cursorVisible;

            FnEventCallback eventCallback;
        };

        WindowData m_data;
    };

} // namespace bbzl
