#pragma once

#include "Matrix.hpp"

namespace vector {
using vec3 = std::array<GLfloat, 3>;
using vec4 = std::array<GLfloat, 4>;
} // namespace vector

vector::vec4 operator*(const Matrix& m, const vector::vec4& v) {
    auto result = vector::vec4{};
    for(auto i = 0u; i < result.size(); i += 1) {
        result[i] = m[i] * v[0] +
                    m[i + 4] * v[1] +
                    m[i + 8] * v[2] +
                    m[i + 12] * v[3];
    }
    return result;
}