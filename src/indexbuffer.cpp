#include "indexbuffer.hpp"
#include <GL/glew.h> // GLEW

namespace Graphics {
    // constructor
    Indexbuffer::Indexbuffer(const List<uint32>& indices)
        : Indexbuffer(indices.data(), indices.size() * sizeof(uint32)) {}
    Indexbuffer::Indexbuffer(const uint32* indices, address size) {
        glGenBuffers(1, &m_ID);
        bind([&]() {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
        });
    }
    // destructor
    Indexbuffer::~Indexbuffer() {
        if (m_ID) {
            glDeleteBuffers(1, &m_ID);
        }
    }
    // data
    void Indexbuffer::setIndices(const uint32* indices, address size, address offset) {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
    }
    // bind
    void Indexbuffer::bind(function<void()> onbind) const {
        if (m_ID) {
            std::lock_guard lock(s_Mutex);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
            onbind();
        }
    }
}