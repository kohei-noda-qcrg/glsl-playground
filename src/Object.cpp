#include "Object.hpp"

Object::Object(GLint size, const std::vector<Vertex>& vertex, const std::optional<std::vector<GLuint>>& index) {
    // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vertex buffer object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), vertex.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

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