#pragma once
#include "object.hpp"

namespace Graphics {
    // Indexbuffer
    class Indexbuffer : public GraphicsObject {
    public:
        // constructor / destructor
        Indexbuffer(const List<uint32>& indices);
        Indexbuffer(const uint32* indices, address size);
        ~Indexbuffer();
        // data
        void setIndices(const uint32* indices, address size, address offset = 0);
        // bind
        void bind(function<void()> onbind) const;
    private:
        // mutex
        static inline mutex s_Mutex;
    };
}