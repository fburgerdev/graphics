#pragma once
#include "common.hpp"
#include "math.hpp"

namespace Graphics {
    class Shader {
    public:
        // constructor / destructor
        Shader(string_view vertexsrc, string_view fragmentsrc);
        ~Shader();
        // bind
        void bind(function<void()> onbind) const;
        // uniform
        // uniform :: int
        void setUniformInt(const std::string& identifier, int32_t val) const;
        void setUniformVec2i(const std::string& identifier, const Math::Vec2i& val) const;
        void setUniformVec3i(const std::string& identifier, const Math::Vec3i& val) const;
        void setUniformVec4i(const std::string& identifier, const Math::Vec4i& val) const;
        // uniform :: float
        void setUniformFloat(const std::string& identifier, float val) const;
        void setUniformVec2f(const std::string& identifier, const Math::Vec2f& val) const;
        void setUniformVec3f(const std::string& identifier, const Math::Vec3f& val) const;
        void setUniformVec4f(const std::string& identifier, const Math::Vec4f& val) const;
        // uniform :: matrix
        void setUniformMat2f(const std::string& identifier, const Math::Mat2f& mat) const;
        void setUniformMat3f(const std::string& identifier, const Math::Mat3f& mat) const;
        void setUniformMat4f(const std::string& identifier, const Math::Mat4f& mat) const;
    private:
        uint32_t CompileShader(int32_t shaderType, const std::string& source);
        uint32_t GetUniformLocation(const std::string& identifier) const;
    private:
        uint32_t m_ID;
        mutable std::unordered_map<std::string, int32_t> m_ULocationCache;
    private:

    };
}