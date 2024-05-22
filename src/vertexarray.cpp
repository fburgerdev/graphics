#include "vertexarray.hpp"
#include <GL/glew.h> // GLEW

namespace Graphics {
    // constructor
    VertexArray::VertexArray(const Vertexbuffer& vertexbuffer, List<VertexAttribute>& layout) {
        glGenVertexArrays(1, &m_ID);
        bind([&]() {
            vertexbuffer.bind([&]() {
                uint32 index = 0;
                address offset = 0;
                for (VertexAttribute attribute : layout) {
                    glEnableVertexAttribArray(index);
                    switch (attribute.dtype) {
                    case VertexDType::INT32:
                        glVertexAttribIPointer(index, attribute.count, GL_INT, sizeof(int32) * attribute.count, (const void*)offset);
                        offset += sizeof(int32) * attribute.count;
                        break;
                    case VertexDType::UINT32:
                        glVertexAttribIPointer(index, attribute.count, GL_UNSIGNED_INT, sizeof(uint32) * attribute.count, (const void*)offset);
                        offset += sizeof(uint32) * attribute.count;
                        break;
                    case VertexDType::FLOAT32:
                        glVertexAttribPointer(index, attribute.count, GL_FLOAT, GL_FALSE, sizeof(float) * attribute.count, (const void*)offset);
                        offset += sizeof(float) * attribute.count;
                        break;
                    case VertexDType::FLOAT64:
                        glVertexAttribPointer(index, attribute.count, GL_DOUBLE, GL_FALSE, sizeof(double) * attribute.count, (const void*)offset);
                        offset += sizeof(double) * attribute.count;
                        break;
                    default:
                        break;
                    }
                }
            });
        });
    }
    // destructor
    VertexArray::~VertexArray() {
        if (m_ID) {
            glDeleteVertexArrays(1, &m_ID);
        }
    }
    // bind
    void VertexArray::bind(function<void()> onbind) const {
        if (m_ID) {
            std::lock_guard lock(s_Mutex);
            glBindVertexArray(m_ID);
            onbind();
        }
    }
}