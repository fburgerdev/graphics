#pragma once
#include "common.hpp"

namespace Graphics {
    // GraphicsObject
    class GraphicsObject {
    public:
        // constructor
        GraphicsObject()
            : m_ID(0) {}
        // copy (delete)
        GraphicsObject(const GraphicsObject&) = delete;
        GraphicsObject& operator=(const GraphicsObject&) = delete;
        // move
        GraphicsObject(GraphicsObject&& other)
            : m_ID(other.m_ID) {
            other.m_ID = 0;
        }
        GraphicsObject& operator=(GraphicsObject&& other) {
            m_ID = other.m_ID;
            other.m_ID = 0;
            return *this;
        }      
        // get
        uint32 getID() const {
            return m_ID;
        }
    protected:
        // member
        uint32 m_ID;
    };
}