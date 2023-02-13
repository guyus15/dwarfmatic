#ifndef GL_DEBUG_H
#define GL_DEBUG_H

#include "glad/glad.h"

#if 1
#define GL_CHECK_ERROR() GL_CheckError(__FILE__, __LINE__)
#else
#define GL_CHECK_ERROR()
#endif

GLenum GL_CheckError(const char* file, int line);

#endif // GL_DEBUG_H
