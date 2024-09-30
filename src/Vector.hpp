#pragma once
#include <GL/glew.h>

#include "Matrix.hpp"

namespace vector {
using Vector = std::array<GLfloat, 4>;
} // namespace vector

vector::Vector operator*(const Matrix& m, const vector::Vector& v) {
    auto result = vector::Vector{};
    for(auto i = 0u; i < result.size(); i += 1) {
        result[i] = m[i] * v[0] +
                    m[i + 4] * v[1] +
                    m[i + 8] * v[2] +
                    m[i + 12] * v[3];
    }
    return result;
}