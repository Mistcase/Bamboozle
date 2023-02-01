#include "Butterfly/butterflypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace butterfly
{
    RenderAPI* RenderCommand::m_renderAPI = new OpenGLRenderAPI();

} // namespace butterfly
