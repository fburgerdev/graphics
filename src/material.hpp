#pragma once
#include "shader.hpp"
#include <variant> // std::variant

namespace Graphics {
    // MaterialParameter
    struct MaterialParameter {
        std::variant<
            int, Math::Vec2i, Math::Vec3i, Math::Vec4i,
            uint, Math::Vec2u, Math::Vec3u, Math::Vec4u,
            float, Math::Vec2f, Math::Vec3f, Math::Vec4f,
            double, Math::Vec2d, Math::Vec3d, Math::Vec4d,
            List<MaterialParameter>, Map<string, MaterialParameter>
        > value;
    };
    // Material
    class Material {
    public:
        // constructor
    private:
        // member
        Shader* m_Shader;
    };
}