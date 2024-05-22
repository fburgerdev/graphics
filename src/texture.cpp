#include "texture.hpp"
#include <GL/glew.h> // GLEW

namespace Graphics {
    // constructor
    Texture::Texture(const char* buffer, const Math::Vec2u& size, const TextureSettings& settings) {
        // create
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glEnable(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)buffer);
        // mipmap
        if (settings.mipmap != TextureMipmap::None) {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        // minfilter
        int32 minfilter;
        if (settings.mipmap == TextureMipmap::None) {
            minfilter = int32(settings.minfilter);
        }
        else if (settings.minfilter == TextureFilter::Linear && settings.mipmap == TextureMipmap::Linear) {
            minfilter = GL_LINEAR_MIPMAP_LINEAR;
        }
        else if (settings.minfilter == TextureFilter::Linear && settings.mipmap == TextureMipmap::Nearest) {
            minfilter = GL_LINEAR_MIPMAP_NEAREST;
        }
        else if (settings.minfilter == TextureFilter::Nearest && settings.mipmap == TextureMipmap::Linear) {
            minfilter = GL_NEAREST_MIPMAP_LINEAR;
        }
        else {
            minfilter = GL_NEAREST_MIPMAP_NEAREST;
        }
        // settings
        // settings :: minfilter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
        // settings :: magfilter
        switch (settings.magfilter) {
        case TextureFilter::Linear:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case TextureFilter::Nearest:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        default:
            break;
        }
        // settings :: horwrap
        switch (settings.horwrap) {
        case TextureWrap::ClampToEdge:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            break;
        case TextureWrap::ClampToBorder:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            break;
        case TextureWrap::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            break;
        case TextureWrap::MirroredRepeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            break;
        default:
            break;
        }
        // settings :: verwrap
        switch (settings.verwrap) {
        case TextureWrap::ClampToEdge:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case TextureWrap::ClampToBorder:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            break;
        case TextureWrap::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case TextureWrap::MirroredRepeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        default:
            break;
        }
    }
    // destructor
    Texture::~Texture() {
        if (m_ID) {
            glDeleteTextures(1, &m_ID);
        }
    }
    // bind
    void Texture::bind(function<void()> onbind, uint32 slot) const {
        if (m_ID) {
            std::lock_guard lock(s_Mutexes[slot]);
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_ID);
            onbind();
        }
    }
}