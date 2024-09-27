#pragma once
#include <array>

#include <GL/glew.h>

class Object {
  protected:
    GLuint vao;
    GLuint vbo;

  public:
    struct Vertex {
        std::array<GLfloat, 3> position;
    };

    void bind() const {
        glBindVertexArray(vao);
    };

    Object(GLint size, GLsizei vertexcount, const Vertex* vertex);
    virtual ~Object();

  private:
    Object(const Object&);
    Object& operator=(const Object&);
};
