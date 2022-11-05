#pragma once

namespace bubble
{
	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};

} // namespace bubble