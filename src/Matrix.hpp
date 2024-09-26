#pragma once
#include <algorithm>
#include <array>

#include <GL/glew.h>

// Matrix transformation clas
class Matrix {

    std::array<GLfloat, 16> matrix;

  public:
    Matrix() {}

    Matrix(const std::array<GLfloat, 16>& matrix) : matrix(matrix) {}

    const GLfloat& operator[](std::size_t i) const {
        return matrix[i];
    }

    GLfloat& operator[](std::size_t i) {
        return matrix[i];
    }

    const GLfloat* data() const {
        return matrix.data();
    }

    /*
     * create an identity matrix
     * 1 0 0 0
     * 0 1 0 0
     * 0 0 1 0
     * 0 0 0 1
     */
    auto loadIdentity() -> void {
        std::fill(matrix.begin(), matrix.end(), 0.0f);
        matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
    }

    static auto identity() -> Matrix {
        Matrix t;
        t.loadIdentity();
        return t;
    }

    /*
     * translate (shift) matrix
     * 1 0 0 x
     * 0 1 0 y
     * 0 0 1 z
     * 0 0 0 1
     */
    static auto translate(GLfloat x, GLfloat y, GLfloat z) -> Matrix {
        Matrix t;
        t.loadIdentity();
        t[12] = x;
        t[13] = y;
        t[14] = z;
        return t;
    }

    /*
     * scale matrix, (x, y, z) times scaling
     * x 0 0 0
     * 0 y 0 0
     * 0 0 z 0
     * 0 0 0 1
     */
    static auto scale(GLfloat x, GLfloat y, GLfloat z) -> Matrix {
        Matrix t;
        t.loadIdentity();
        t[0]  = x;
        t[5]  = y;
        t[10] = z;
    }
};