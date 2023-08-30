#pragma once

#include <glad/glad.h>
#include <cstdio>

namespace bbzl
{
#if defined(DEBUG)
#define GL_CALL(call)									\
	call;												\
    _dbg_CheckOpenGLError(#call, __FILE__, __LINE__);
#else
#define GL_CALL(call) call
#endif

	static void _dbg_CheckOpenGLError(const char* msg, const char* fname, int line)
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			printf("OpenGL error %08x, at %s:%i - for %s\n", err, fname, line, msg);
			assert(false);
		}
	}

} // namespace bbzl
