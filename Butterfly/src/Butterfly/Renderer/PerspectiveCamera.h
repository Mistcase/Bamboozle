#pragma once

#include "Butterfly/Scene/Entity.h"

#include <glm/glm.hpp>

namespace butterfly
{
    class Event;
    class MouseMovedEvent;
    class KeyEvent;

    class PerspectiveCamera
    {
    public:
		void possess(Entity entity);

        void update(float dt);

        void onEvent(Event& event);

        Entity getPawn() const;
        glm::vec3 getViewDirection() const;
        const glm::mat4& getViewProjection() const;

    private:
        void updateViewProjection();

        bool onMouseMovedEvent(MouseMovedEvent& mouseEvent);
        bool onKeyEvent(KeyEvent& keyEvent);

    private:
        glm::mat4 m_viewProjection;

	private:
		Entity m_entity;
    };

} // namespace butterfly
