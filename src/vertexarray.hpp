#pragma once
#include "vertexbuffer.hpp"
#include "vertex.hpp"

namespace Graphics {
    // VertexArray
    class VertexArray : public GraphicsObject {
    public:
        // constructor / destructor
        VertexArray(const Vertexbuffer& vertexbuffer, List<VertexAttribute>& layout);
        ~VertexArray();
        // bind
        void bind(function<void()> onbind) const;
    private:
        // mutex
        static inline mutex s_Mutex;
    };
}