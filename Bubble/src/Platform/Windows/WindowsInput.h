#pragma once

#include "Bubble/Input.h"

namespace bubble
{
	class WindowsInput : public Input
	{
	protected:
		bool isKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;

		std::pair<float, float> getMousePositionImpl() override;
		float getMouseXImpl() override;
		float getMouseYImpl() override;
	};

} // namespace bubble