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
} // namespace shape_example