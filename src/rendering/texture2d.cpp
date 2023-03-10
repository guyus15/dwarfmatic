/**
 * \file texture2d.cpp
 */

#include "texture2d.h"
#include "utils/logging.h"
#include "utils/profiling.h"

Texture2D::Texture2D()
    : m_id{},
    m_internal_format{ GL_RGB },
    m_image_format{ GL_RGB },
    m_wrap_s{ GL_REPEAT },
    m_wrap_t{ GL_REPEAT },
    m_filter_min{ GL_LINEAR },
    m_filter_mag{ GL_LINEAR },
    m_width{},
    m_height{}
{
}

Texture2D::~Texture2D()
{
    DFM_PROFILE_FUNCTION();
    glDeleteTextures(1, &m_id);
}

/**
 * \brief Generates a 2D texture.
 * \param width The width of the texture.
 * \param height The height of the texture. 
 * \param data The texture data.
 */
void Texture2D::Generate(const int width, const int height, const unsigned char* data)
{
    DFM_PROFILE_FUNCTION();

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_mag);

    m_width = width;
    m_height = height;

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_image_format, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        DFM_CORE_ERROR("Failed to generate texture.");
        return;
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * \brief Binds the texture for use.
 */
void Texture2D::Bind() const
{
    DFM_PROFILE_FUNCTION();

    glBindTexture(GL_TEXTURE_2D, m_id);
}

/**
 * \brief Enables the texture's alpha channel.
 * \param enable Enables the alpha channel when true, otherwise the alpha channel is disabled.
 */
void Texture2D::EnableAlpha(const bool enable)
{
    DFM_PROFILE_FUNCTION();

    if (enable)
    {
        m_internal_format = GL_RGBA;
        m_image_format = GL_RGBA;
    }
    else
    {
        m_internal_format = GL_RGB;
        m_image_format = GL_RGB;
    }
}
