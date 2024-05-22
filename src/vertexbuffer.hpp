#pragma once
#include "object.hpp"

namespace Graphics {
    // Vertexbuffer
    class Vertexbuffer : public GraphicsObject {
    public:
        // constructor / destructor
        template<typename TVertex>
        Vertexbuffer(const List<TVertex>& vertices)
            : Vertexbuffer(vertices.data(), vertices.size() * sizeof(TVertex)) {}
        Vertexbuffer(const void* vertices, address size);
        ~Vertexbuffer();
        // data
        void setData(const void* vertices, address size, address offset = 0);
        // bind
        void bind(function<void()> onbind) const;
    private:
        // mutex
        static inline mutex s_Mutex;
    };
}