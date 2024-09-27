#pragma once
#include <source_location>

#include "util/print.hpp"

#include "Shape.hpp"

class ShapeIndex : public Shape {
  protected:
    const std::vector<GLuint> index;

  public:
    ShapeIndex(const std::vector<Object::Vertex>& vertex, const std::vector<GLuint>& index)
        : Shape(vertex, index), index(index) {}

    virtual auto execute() const -> void {
        glDrawElements(GL_LINES, index.size(), GL_UNSIGNED_INT, 0);
    }
};