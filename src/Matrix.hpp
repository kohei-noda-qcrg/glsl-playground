#pragma once
#include <algorithm>
#include <array>
#include <cmath>

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

    /*
     * Rotate matrix around x-axis
     * angle in radians (0 to 2PI)
     * 1 0           0          0
     * 0 cos(angle) -sin(angle) 0
     * 0 sin(angle)  cos(angle) 0
     * 0 0           0          1
     */
    static auto rotateX(GLfloat angle) -> Matrix {
        Matrix t;
        t.loadIdentity();
        t[5]  = std::cos(angle);
        t[6]  = -std::sin(angle);
        t[9]  = std::sin(angle);
        t[10] = std::cos(angle);
        return t;
    }

    /*
     * Rotate matrix around y-axis
     * angle in radians (0 to 2PI)
     * cos(angle) 0 sin(angle) 0
     * 0          1          0 0
     * -sin(angle) 0 cos(angle) 0
     * 0          0          0 1
     */
    static auto rotateY(GLfloat angle) -> Matrix {
        Matrix t;
        t.loadIdentity();
        t[0]  = std::cos(angle);
        t[2]  = std::sin(angle);
        t[8]  = -std::sin(angle);
        t[10] = std::cos(angle);
        return t;
    }

    /*
     * Rotate matrix around z-axis
     * angle in radians (0 to 2PI)
     * cos(angle) -sin(angle) 0 0
     * sin(angle)  cos(angle) 0 0
     * 0          0           1 0
     * 0          0           0 1
     */
    static auto rotateZ(GLfloat angle) -> Matrix {
        Matrix t;
        t.loadIdentity();
        t[0] = std::cos(angle);
        t[1] = -std::sin(angle);
        t[4] = std::sin(angle);
        t[5] = std::cos(angle);
        return t;
    }

    /*
     * Rotate matrix around arbitrary axis
     * d = sqrt(x*x + y*y + z*z)
     * l = x/d, m = y/d, n = z/d
     * angle(θ) in radians (0 to 2PI)
     * l^2+(1-l^2)cos(θ)      l*m(1-cos(θ))-n*sin(θ) l*n(1-cos(θ))+m*sin(θ) 0
     * l*m(1-cos(θ))+n*sin(θ) m^2+(1-m^2)cos(θ)      m*n(1-cos(θ))-l*sin(θ) 0
     * l*n(1-cos(θ))-m*sin(θ) m*n(1-cos(θ))+l*sin(θ) n^2+(1-n^2)cos(θ)      0
     * 0                      0                      0                      1
     */
    static auto rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
        Matrix t;
        t.loadIdentity();
        GLfloat d = std::sqrt(x * x + y * y + z * z);
        if(d < 0.0f) return t; // invalid axis, return identity matrix because it's not going to change anything
        GLfloat l = x / d, m = y / d, n = z / d;
        GLfloat cosT = std::cos(angle), sinT = std::sin(angle);
        t[0] = pow(l, 2) + (1 - pow(l, 2)) * cosT;
        t[1] = l * m * (1 - cosT) - n * sinT;
        t[2] = l * n * (1 - cosT) + m * sinT;
        t[4] = l * m * (1 - cosT) + n * sinT;
        t[5] = pow(m, 2) + (1 - pow(m, 2)) * cosT;
        t[6] = m * n * (1 - cosT) - l * sinT;
        t[8] = l * n * (1 - cosT) - m * sinT;
        t[9] = m * n * (1 - cosT) + l * sinT;
        t[10] = pow(n, 2) + (1 - pow(n, 2)) * cosT;
        return t;
    }
};