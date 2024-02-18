#pragma once

#include "Bamboozle/Events/Event.h"

namespace bbzl
{

    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& _title = "Bamboozle Engine",
                    unsigned int _width = 1280,
                    unsigned int _height = 720)
            : title(_title)
            , width(_width)
            , height(_height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class Window
    {
    public:
        using FnEventCallback = std::function<void(Event&)>;

    public:
        static Window* Create(const WindowProps& props = WindowProps());

    public:
        virtual ~Window() = default;

        virtual void createSurface(void* data) = 0;

        virtual void onUpdate() = 0;

        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        // Window attributes
        virtual void setEventCallback(const FnEventCallback& callback) = 0;
		virtual void setCursorVisible(bool visible) = 0;
        virtual void setVSync(bool enabled) = 0;

        virtual bool isVSync() const = 0;
		virtual bool isCursorVisible() const = 0;
        virtual void* getNativeWindow() const = 0;
    };

} // namespace bbzl
