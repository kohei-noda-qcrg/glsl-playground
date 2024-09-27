#pragma once
#include <array>
#include <optional>
#include <vector>

#include <GL/glew.h>

class Object {
  protected:
    GLuint vao; // summit array object
    GLuint vbo; // summit buffer object
    GLuint ibo; // summit buffer object for index

  public:
    struct Vertex {
        GLfloat position[3];
        GLfloat color[3];
    };

    void bind() const {
        glBindVertexArray(vao);
    };

    Object(GLint size, const std::vector<Vertex>& vertex, const std::optional<std::vector<GLuint>>& index = std::nullopt);
    virtual ~Object();

  private:
    Object(const Object&);
    Object& operator=(const Object&);
};
