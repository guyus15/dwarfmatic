#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

class Texture2D
{
public:
    Texture2D();
    ~Texture2D();

    Texture2D(const Texture2D&) = default;
    Texture2D(Texture2D&&) noexcept = default;

    Texture2D& operator=(const Texture2D&) = default;
    Texture2D& operator=(Texture2D&&) noexcept = default;

    void Generate(int width, int height, unsigned char* data);
    void Bind() const;
    void EnableAlpha(bool enable);

private:
    GLuint m_id;
    GLint m_internal_format;
    GLint m_image_format;
    GLint m_wrap_s, m_wrap_t;
    GLint m_filter_min, m_filter_mag;
    GLsizei m_width, m_height;
};

#endif // TEXTURE_H