#pragma once

#include "Shape.hpp"

class SolidShape : public Shape {
    public:
    SolidShape(const std::vector<Object::Vertex>& vertex):
        Shape(vertex) {}

    virtual auto execute() const -> void {
        glDrawArrays(GL_TRIANGLES, 0, vertexcount);
    }
};