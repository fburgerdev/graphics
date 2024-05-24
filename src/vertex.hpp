#pragma once
#include "common.hpp"

namespace Graphics {
    // VertexDType
    enum class VertexDType {
        INT32, UINT32, FLOAT32, FLOAT64
    };
    // VertexAttribute
    struct VertexAttribute {
        // constructor
        VertexAttribute(VertexDType dtype, uint count = 1)
            : dtype(dtype), count(count) {}
        // member
        VertexDType dtype;
        uint count;
    };
}