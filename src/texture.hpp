#pragma once
#include "object.hpp"
#include "math.hpp"

namespace Graphics {
    // TextureWrap
    enum class TextureWrap {
        ClampToEdge, ClampToBorder, Repeat, MirroredRepeat
    };
    // TextureFilter
    enum class TextureFilter {
        Linear, Nearest
    };
    // TextureMipmap
    enum class TextureMipmap {
        None, Linear, Nearest
    };
    // TextureSettings
    struct TextureSettings {
        TextureWrap horwrap = TextureWrap::ClampToEdge;
        TextureWrap verwrap = TextureWrap::ClampToEdge;
        TextureFilter magfilter = TextureFilter::Linear;
        TextureFilter minfilter = TextureFilter::Linear;
        TextureMipmap mipmap = TextureMipmap::None;
    };
    // Texture
    class Texture : public GraphicsObject {
    public:
        // constructor / destructor
        Texture(const char* buffer, const Math::Vec2u& size, const TextureSettings& settings = TextureSettings());
        ~Texture();
        // bind
        void bind(function<void()> onbind, uint32 slot = 0) const;
    private:
        // mutex
        static inline Map<uint32, mutex> s_Mutexes;
    };
}