/**
 * \file gl_debug.h
 */

#ifndef GL_DEBUG_H
#define GL_DEBUG_H

#include "glad/glad.h"

#if 1
#define GL_CHECK_ERROR() GL_CheckError(__FILE__, __LINE__)
#else
#define GL_CHECK_ERROR()
#endif

/**
 * \brief Checks to see if an OpenGL error has occured.
 * \param file The name of the file in which the GL function is called.
 * \param line The line in which the GL function is called.
 * \return The type of GL error.
 */
GLenum GL_CheckError(const char* file, int line);

#endif // GL_DEBUG_H
