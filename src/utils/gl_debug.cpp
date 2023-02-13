#include "utils/gl_debug.h"

#include <iostream>
#include <string>

GLenum GL_CheckError(const char* file, int line)
{
    GLenum error_code;

    while ((error_code = glGetError()) != GL_NO_ERROR)
    {
        std::string error_text;

        switch (error_code)
        {
        case GL_INVALID_ENUM:
            error_text = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error_text = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error_text = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error_text = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error_text = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error_text = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error_text = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        }

        std::cerr << "OpenGL error: " << error_text << ". '" << file << " @ " << line << "\n";
    }

    return error_code;
}
