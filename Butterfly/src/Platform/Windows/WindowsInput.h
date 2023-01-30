#pragma once

#include "Butterfly/Input.h"

namespace butterfly
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

} // namespace butterfly
