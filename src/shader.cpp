#include "shader.hpp"
#include "logging.hpp"
#include <GL/glew.h> // GLEW

namespace Graphics {
    // compile
    static uint32 compile(int32 shaderType, string_view source) {
        uint32 id = glCreateShader(shaderType);
        const char* sourccstr = source.data();
        glShaderSource(id, 1, &sourccstr, nullptr);
        glCompileShader(id);
        int32 result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int32 length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetShaderInfoLog(id, length, &length, message);
            glDeleteShader(id);
            LOG_ERROR("Shader compilation failed!\n\nMessage\n{}\nSource\n{}", message, source);
            delete[] message;
            return 0;
        }
        return id;
    }

    // constructor / destructor
    Shader::Shader(string_view vertexsrc, string_view fragmentsrc) {
        // TODO: error handling
        // create
        m_ID = glCreateProgram();
        uint32 vs = compile(GL_VERTEX_SHADER, vertexsrc);
        uint32 fs = compile(GL_FRAGMENT_SHADER, fragmentsrc);
        // link
        glAttachShader(m_ID, vs);
        glAttachShader(m_ID, fs);
        glLinkProgram(m_ID);
        glValidateProgram(m_ID);
        // delete
        glDeleteShader(vs);
        glDeleteShader(fs);
    }
    Shader::~Shader() {
        if (m_ID) {
            glDeleteProgram(m_ID);
        }
    }
    // bind
    void Shader::bind(function<void()> onbind) const {
        if (m_ID) {
            std::lock_guard lock(s_Mutex);
            glUseProgram(m_ID);
            onbind();
        }
    }
    // uniform
    // uniform :: int
    void Shader::setUniformInt(const string& name, int32_t value) {
        glUniform1i(getUniformID(name), value);
    }
    void Shader::setUniformVec2i(const string& name, const Math::Vec2i& value) {
        glUniform2i(getUniformID(name), value.x, value.y);
    }
    void Shader::setUniformVec3i(const string& name, const Math::Vec3i& value) {
        glUniform3i(getUniformID(name), value.x, value.y, value.z);
    }
    void Shader::setUniformVec4i(const string& name, const Math::Vec4i& value) {
        glUniform4i(getUniformID(name), value.x, value.y, value.z, value.w);
    }
    // uniform :: float
    void Shader::setUniformFloat(const string& name, float value) {
        glUniform1f(getUniformID(name), value);
    }
    void Shader::setUniformVec2f(const string& name, const Math::Vec2f& value) {
        glUniform2f(getUniformID(name), value.x, value.y);
    }
    void Shader::setUniformVec3f(const string& name, const Math::Vec3f& value) {
        glUniform3f(getUniformID(name), value.x, value.y, value.z);
    }
    void Shader::setUniformVec4f(const string& name, const Math::Vec4f& value) {
        glUniform4f(getUniformID(name), value.x, value.y, value.z, value.w);
    }
    // uniform :: matrix
    void Shader::setUniformMat2f(const string& name, const Math::Mat2f& mat) {
        glUniformMatrix2fv(getUniformID(name), 1, GL_FALSE, mat.data());
    }
    void Shader::setUniformMat3f(const string& name, const Math::Mat3f& mat) {
        glUniformMatrix3fv(getUniformID(name), 1, GL_FALSE, mat.data());
    }
    void Shader::setUniformMat4f(const string& name, const Math::Mat4f& mat) {
        glUniformMatrix4fv(getUniformID(name), 1, GL_FALSE, mat.data());
    }
    // uniform :: id
    uint32 Shader::getUniformID(const string& name) const {
        if (m_UniformIDCache.contains(name)) {
            return m_UniformIDCache[name];
        }
        uint32 id = glGetUniformLocation(m_ID, name.c_str());
        m_UniformIDCache[name] = id;
        return id;
    }
}