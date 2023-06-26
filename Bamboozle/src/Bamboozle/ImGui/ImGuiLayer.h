#pragma once

#include "Bamboozle/Events/ApplicationEvent.h"
#include "Bamboozle/Events/KeyEvent.h"
#include "Bamboozle/Events/MouseEvent.h"
#include "Bamboozle/Layer.h"

namespace bbzl
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;
        void onImGuiRender() override;

        void begin();
        void end();

    private:
        float m_time = 0.0f;
    };

} // namespace bbzl
