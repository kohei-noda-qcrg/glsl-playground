#pragma once
#include <memory>

#include <GL/glew.h>

template <typename T>
class Uniform {
    struct UniformBuffer {
        // uniform buffer object
        GLuint ubo;
        // size of the ubo
        GLsizeiptr blocksize;
        /// @brief constructor of uniform buffer object(ubo)
        /// @param data data that is stored to uniform block
        /// @param count number of uniform blocks to allocate
        UniformBuffer(const T* data, size_t count) {
            auto alignment = GLint{};
            glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &alignment);
            blocksize = (((sizeof(T) - 1) / alignment) + 1) * alignment;
            glGenBuffers(1, &ubo);
            glBindBuffer(GL_UNIFORM_BUFFER, ubo);
            glBufferData(GL_UNIFORM_BUFFER, count * blocksize, NULL, GL_STATIC_DRAW);
            for(auto i = 0u; i < count; i += 1) {
                glBufferSubData(GL_UNIFORM_BUFFER, i * blocksize, sizeof(T), data + i);
            }
        }
        ~UniformBuffer() {
            glDeleteBuffers(1, &ubo);
        }
    };

    const std::shared_ptr<const UniformBuffer> buffer;

  public:
    Uniform(const T* data = NULL, size_t count = 1) : buffer(new UniformBuffer(data, count)){};
    virtual ~Uniform(){};

    // store data to the uniform buffer object
    auto set(const T* data, size_t start = 0, size_t count = 1) const -> void {
        glBindBuffer(GL_UNIFORM_BUFFER, buffer->ubo);
        for(auto i = 0u; i < count; i += 1) {
            glBufferSubData(GL_UNIFORM_BUFFER, (start + i) * buffer->blocksize, sizeof(T), data + 1);
        }
    }

    /// @brief use this uniform buffer object
    /// @param bp bonding point
    /// @param i how many buffer index to start bonding from
    auto select(GLuint bp, size_t i = 0) const -> void {
        glBindBufferRange(GL_UNIFORM_BUFFER, bp, buffer->ubo, i * buffer->blocksize, sizeof(T));
    }
};