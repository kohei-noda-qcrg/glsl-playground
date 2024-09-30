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

const auto solidCubeVertex = std::vector<Object::Vertex>{
    // left
    {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    {{-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
    // back
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}},
    // bottom
    {{-1.0f, -1.0f, -1.0f}, {0.0f - 1.0f, 0.0f}},
    {{1.0f, -1.0f, -1.0f}, {0.0f - 1.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {0.0f - 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f - 1.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {0.0f - 1.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f - 1.0f, 0.0f}},
    // right
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    // top
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
    // front
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}};

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
    0, 1, 2, 3, 4, 5,       // left
    6, 7, 8, 9, 10, 11,     // back
    12, 13, 14, 15, 16, 17, // bottom
    18, 19, 20, 21, 22, 23, // right
    24, 25, 26, 27, 28, 29, // top
    30, 31, 32, 33, 34, 35  // front
};

constexpr auto slices = 16, stacks = 8;
const auto     solidSphereVertex = std::vector<Object::Vertex>([]() {
    auto vertices = std::vector<Object::Vertex>();
    for(auto j = 0; j <= stacks; ++j) {
        const auto theta = j * M_PI / stacks;
        const auto y = float(std::cos(theta)), r = float(std::sin(theta));
        for(auto i = 0; i <= slices; ++i) {
            const auto phi = i * 2 * M_PI / slices;
            const auto z = float(r * std::cos(phi)), x = float(r * std::sin(phi));

            const auto v = Object::Vertex{{x, y, z}, {x, y, z}};
            vertices.emplace_back(v);
        }
    }
    return vertices;
}());

const auto solidSphereIndex = std::vector<GLuint>([]() {
    auto indices = std::vector<GLuint>();
    for(auto j = 0; j < stacks; ++j) {
        const auto k = j * (slices + 1);
        for(auto i = 0; i < slices; ++i) {
            const auto k0 = k + i;
            const auto k1 = k0 + 1;
            const auto k2 = k1 + slices;
            const auto k3 = k2 + 1;
            indices.emplace_back(k0);
            indices.emplace_back(k2);
            indices.emplace_back(k3);
            indices.emplace_back(k0);
            indices.emplace_back(k3);
            indices.emplace_back(k1);
        }
    }
    return indices;
}());

} // namespace shape_example