#include "texture2d.h"

#include <iostream>
#include "texture2d.h"

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
    glDeleteTextures(1, &m_id);
}

void Texture2D::Generate(const int width, const int height, unsigned char* data)
{
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
        std::cerr << "Error: Failed to generate texture.\n";
        return;
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::EnableAlpha(bool enable)
{
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
