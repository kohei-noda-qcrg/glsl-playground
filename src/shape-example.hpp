#pragma once

#include "Object.hpp"

namespace shape_example {
const auto octahedronVertex = std::vector<Object::Vertex>{
    {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
    {{-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.8f}},
    {{0.0f, -1.0f, 0.0f}, {0.0f, 0.8f, 0.0f}},
    {{1.0f, 0.0f, 0.0f}, {0.0f, 0.8f, 0.8f}},
    {{0.0f, 1.0f, 0.0f}, {0.8f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 1.0f}, {0.8f, 0.0f, 0.8f}},
    {{0.0f, -1.0f, 0.0f}, {0.8f, 0.8f, 0.0f}},
    {{0.0f, 0.0f, -1.0f}, {0.8f, 0.8f, 0.8f}},
    {{-1.0f, 0.0f, 0.0f}, {0.8f, 0.0f, 0.0f}},
    {{0.0f, 0.0f, 1.0f}, {0.0f, 0.8f, 0.0f}},
    {{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.8f}},
    {{0.0f, 0.0f, -1.0f}, {0.8f, 0.0f, 0.8f}}};

const auto cubeVertex = std::vector<Object::Vertex>{
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 0.8f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.8f, 0.0f}},
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.8f, 0.8f}},
    {{1.0f, 1.0f, -1.0f}, {0.8f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, -1.0f}, {0.8f, 0.0f, 0.8f}},
    {{1.0f, -1.0f, 1.0f}, {0.8f, 0.8f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.8f, 0.8f, 0.8f}}};

const auto wireCubeIndex = std::vector<GLuint>{
    1, 0,
    2, 7,
    3, 0,
    4, 7,
    5, 0,
    6, 7,
    1, 2,
    2, 3,
    3, 4,
    4, 5,
    5, 6,
    6, 1};

const auto solidCubeIndex = std::vector<GLuint>{
    0, 1, 2, 0, 2, 3, // left
    0, 3, 4, 0, 4, 5, // back
    0, 5, 6, 0, 6, 1, // bottom
    7, 6, 5, 7, 5, 4, // right
    7, 4, 3, 7, 3, 2, // top
    7, 2, 1, 7, 1, 6  // front
};

} // namespace shape_example