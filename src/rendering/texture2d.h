/**
 * \file texture2d.h
 */

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "glad/glad.h"

/**
 * \brief Represents a 2D texture.
 */
class Texture2D
{
public:
    Texture2D();
    ~Texture2D();

    Texture2D(const Texture2D&) = default;
    Texture2D(Texture2D&&) noexcept = default;

    Texture2D& operator=(const Texture2D&) = default;
    Texture2D& operator=(Texture2D&&) noexcept = default;

    /**
     * \brief Generates a 2D texture.
     * \param width The width of the texture.
     * \param height The height of the texture.
     * \param data The texture data.
     */
    void Generate(int width, int height, const unsigned char* data);

    /**
     * \brief Binds the texture for use.
     */
    void Bind() const;

    /**
     * \brief Enables the texture's alpha channel.
     * \param enable Enables the alpha channel when true, otherwise the alpha channel is disabled.
     */
    void EnableAlpha(bool enable);

private:
    GLuint m_id;
    GLint m_internal_format;
    GLint m_image_format;
    GLint m_wrap_s, m_wrap_t;
    GLint m_filter_min, m_filter_mag;
    GLsizei m_width, m_height;
};

#endif // TEXTURE2D_H