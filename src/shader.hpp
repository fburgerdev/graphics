#pragma once
#include "object.hpp"
#include "math.hpp"

namespace Graphics {
    class Shader : GraphicsObject{
    public:
        // constructor / destructor
        Shader(string_view vertexsrc, string_view fragmentsrc);
        ~Shader();
        // bind
        void bind(function<void()> onbind) const;
        // uniform
        // uniform :: int
        void setUniformInt(const string& name, int32_t value) const;
        void setUniformVec2i(const string& name, const Math::Vec2i& value) const;
        void setUniformVec3i(const string& name, const Math::Vec3i& value) const;
        void setUniformVec4i(const string& name, const Math::Vec4i& value) const;
        // uniform :: float
        void setUniformFloat(const string& name, float value) const;
        void setUniformVec2f(const string& name, const Math::Vec2f& value) const;
        void setUniformVec3f(const string& name, const Math::Vec3f& value) const;
        void setUniformVec4f(const string& name, const Math::Vec4f& value) const;
        // uniform :: matrix
        void setUniformMat2f(const string& name, const Math::Mat2f& mat) const;
        void setUniformMat3f(const string& name, const Math::Mat3f& mat) const;
        void setUniformMat4f(const string& name, const Math::Mat4f& mat) const;
    private:
        // uniform :: id
        uint32 getUniformID(const string& name) const;
        // member
        mutable HashMap<string, uint32> m_UniformIDCache;
        // mutex
        static inline mutex s_Mutex;
    };
}