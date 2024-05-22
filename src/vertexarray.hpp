#pragma once
#include "vertexbuffer.hpp"
#include "vertex.hpp"

namespace Graphics {
    // VertexArray
    class VertexArray : public GraphicsObject {
    public:
        // constructor / destructor
        VertexArray(const Vertexbuffer& vertexbuffer, List<VertexAttribute>& layout);
        template<typename TVertex>
        VertexArray(const List<TVertex>& vertices)
            : m_Vertexbuffer(vertices) {
            create(m_Vertexbuffer.value(), TVertex::getAttributes());
        }
        ~VertexArray();
        // bind
        void bind(function<void()> onbind) const;
    private:
        // create
        void create(const Vertexbuffer& vertexbuffer, List<VertexAttribute>& layout);
        // member
        Opt<Vertexbuffer> m_Vertexbuffer;
        // mutex
        static inline mutex s_Mutex;
    };
}