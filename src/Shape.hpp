#pragma once
#include <memory>

#include <GL/gl.h>

#include "Object.hpp"

class Shape {
  private:
    std::shared_ptr<const Object> object;

  protected:
    const GLsizei vertexcount;

  public:
    Shape(const std::vector<Object::Vertex>& vertex, const std::optional<std::vector<GLuint>>& index = std::nullopt)
        : object(std::make_shared<Object>(vertex, index)),
          vertexcount(vertex.size()) {}

    auto draw() const -> void {
        object->bind();
        execute();
    };

    virtual auto execute() const -> void {
        glDrawArrays(GL_LINE_LOOP, 0, vertexcount);
    }
};