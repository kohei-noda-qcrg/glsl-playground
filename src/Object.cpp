#include "util/print.hpp"

#include "Object.hpp"

Object::Object(GLint size, const std::vector<Vertex>& vertex, const std::optional<std::vector<GLuint>>& index) {
    // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), vertex.data(), GL_STATIC_DRAW);

    const auto gpu_pos = static_cast<Vertex *>(0)->position;
    glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), gpu_pos);
    glEnableVertexAttribArray(0);
    const auto gpu_color = static_cast<Vertex *>(0)->color;
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), gpu_color);
    glEnableVertexAttribArray(1);
    print("gpu_pos: ", gpu_pos, " gpu_color: ", gpu_color);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    const auto idx_size = index.has_value() ? index->size() : 0;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx_size * sizeof(GLuint), index->data(), GL_STATIC_DRAW);
}

Object::~Object() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ibo);
}