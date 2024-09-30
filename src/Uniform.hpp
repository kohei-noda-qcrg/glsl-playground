#pragma once
#include <memory>

#include <GL/glew.h>

template <typename T>
class Uniform {
    struct UniformBuffer {
        // uniform buffer object
        GLuint ubo;
        UniformBuffer(const T* data) {
            glGenBuffers(1, &ubo);
            glBindBuffer(GL_UNIFORM_BUFFER, ubo);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(T), data, GL_STATIC_DRAW);
        }
        ~UniformBuffer() {
            glDeleteBuffers(1, &ubo);
        }
    };

    const std::shared_ptr<const UniformBuffer> buffer;

  public:
    Uniform(const T* data = NULL) : buffer(new UniformBuffer(data)){};
    virtual ~Uniform(){};

    // store data to the uniform buffer object
    auto set(const T* data) const -> void {
        glBindBuffer(GL_UNIFORM_BUFFER, buffer->ubo);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), data);
    }

    /// @brief use this uniform buffer object
    /// @param bp bonding point
    auto select(GLuint bp) const -> void {
        glBindBufferBase(GL_UNIFORM_BUFFER, bp, buffer->ubo);
    }
};