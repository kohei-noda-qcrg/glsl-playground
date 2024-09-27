#pragma once

#include "ShapeIndex.hpp"

class SolidShapeIndex : public ShapeIndex {
  public:
    SolidShapeIndex(const std::vector<Object::Vertex>& vertex, const std::vector<GLuint>& index) : ShapeIndex(vertex, index) {}

    virtual auto execute() const -> void {
        glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT, 0);
    }
};