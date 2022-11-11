#include "bubblepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace bubble
{
    RenderAPI* RenderCommand::m_renderAPI = new OpenGLRenderAPI();

} // namespace bubble
