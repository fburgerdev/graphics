#include "vertexbuffer.hpp"
#include <GL/glew.h> // GLEW

namespace Graphics {
    // constructor
    Vertexbuffer::Vertexbuffer(const void* vertices, address size) {
        glGenBuffers(1, &m_ID);
        bind([&]() {
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
        });
    }
    // destructor
    Vertexbuffer::~Vertexbuffer() {
        if (m_ID) {
            glDeleteBuffers(1, &m_ID);
        }
    }
    // data
    void Vertexbuffer::setData(const void* vertices, address size, address offset) {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices);
    }
    // bind
    void Vertexbuffer::bind(function<void()> onbind) const {
        if (m_ID) {
            std::lock_guard lock(s_Mutex);
            glBindBuffer(GL_ARRAY_BUFFER, m_ID);
            onbind();
        }
    }
}