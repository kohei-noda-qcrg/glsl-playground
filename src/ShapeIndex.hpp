#pragma once
#include <source_location>

#include "util/print.hpp"

#include "Shape.hpp"

class ShapeIndex : public Shape {
  protected:
    const std::optional<std::vector<GLuint>> index;

  public:
    ShapeIndex(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, const std::optional<std::vector<GLuint>>& index = std::nullopt)
        : Shape(size, vertexcount, vertex, index), index(index) {
          print("index hasvalue: ", index.has_value(), ", index size: ", index->size());
        }

    virtual auto execute() const -> void {
        if(!index.has_value()) {
            const auto cur = std::source_location::current();
            warn(cur.file_name(), " : ", cur.function_name(), " : index has no value, cannot draw elements");
            return;
        }
        glDrawElements(GL_LINES, index->size(), GL_UNSIGNED_INT, 0);
    }
};