#include "util/print.hpp"

#include "Object.hpp"

Object::Object(const std::vector<Vertex>& vertex, const std::optional<std::vector<GLuint>>& index) {
    // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), vertex.data(), GL_STATIC_DRAW);

    // vertex position
    const auto gpu_pos  = reinterpret_cast<const void*>(offsetof(Vertex, position));
    constexpr auto size_pos = sizeof(Vertex::position) / sizeof(Vertex::position[0]);
    glVertexAttribPointer(0, size_pos, GL_FLOAT, GL_FALSE, sizeof(Vertex), gpu_pos);
    glEnableVertexAttribArray(0);

    // vertex normal vector
    const auto gpu_normal  = reinterpret_cast<const void*>(offsetof(Vertex, normal));
    constexpr auto size_normal = sizeof(Vertex::normal) / sizeof(Vertex::normal[0]);
    glVertexAttribPointer(1, size_normal, GL_FLOAT, GL_FALSE, sizeof(Vertex), gpu_normal);
    glEnableVertexAttribArray(1);

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