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
    Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex, const std::optional<std::vector<GLuint>>& index = std::nullopt)
        : object(std::make_shared<Object>(size, vertexcount, vertex, index)),
          vertexcount(vertexcount) {}

    void draw() const {
        object->bind();
        execute<GL_LINE_LOOP>();
    };

    template <GLenum mode>
    void execute() const {
        glDrawArrays(mode, 0, vertexcount);
    }
};