#include "RenderCommand.h"

#include "Bamboozle/bbzl.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace bbzl
{
    RenderAPI* RenderCommand::m_renderAPI = new OpenGLRenderAPI();

} // namespace bbzl
