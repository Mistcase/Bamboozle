#pragma once

namespace butterfly
{
	class Event;
	class PerspectiveCamera;

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(PerspectiveCamera* camera);

		void onUpdate(float dt);
		void onEvent(Event& event);

	private:
		PerspectiveCamera* m_camera;

	};

} // namespace butterflyx
