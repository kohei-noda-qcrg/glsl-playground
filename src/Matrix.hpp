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

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix res;
        for(int i = 0; i < 16; i += 1) {
            const int j = i & 3;
            const int k = i & ~3;
            res[i] =
                matrix[j] * other[k] +
                matrix[j + 4] * other[k + 1] +
                matrix[j + 8] * other[k + 2] +
                matrix[j + 12] * other[k + 3];
        }

        return res;
    }

    const GLfloat* data() const {
        return matrix.data();
    }

    /// @brief create an view transform matrxi
    /// @param pov point of view (camera position)
    /// @param target target position
    /// @param up up vector, (0, 1, 0) is common
    /// @return view matrix
    static auto lookAt(const std::array<GLfloat, 3>& pov, const std::array<GLfloat, 3>& target, const std::array<GLfloat, 3>& up) -> Matrix {
        const auto povx = pov[0], povy = pov[1], povz = pov[2];
        const auto trgx = target[0], trgy = target[1], trgz = target[2];
        const auto upx = up[0], upy = up[1], upz = up[2];

        // create a tranform matrix that moves the camera to the origin
        const auto tv = translate(-povx, -povy, -povz);
        // new z-axis (labelled t axis) is target - pov
        const auto tx = trgx - povx, ty = trgy - povy, tz = trgz - povz;
        // new y-axis (labelled r axis) is up*t (* means cross product)
        const auto rx = upy * tz - upz * ty, ry = upz * tx - upx * tz, rz = upx * ty - upy * tx;
        // new x-axis (labelled s axis) is t*r (* means cross product)
        const auto sx = ty * rz - tz * ry, sy = tz * rx - tx * rz, sz = tx * ry - ty * rx;

        if((pow(sx, 2) + pow(sy, 2) + pow(sz, 2)) == 0) return tv; // invalid axis length

        // normalize s, r, t axis and create rotation matrix
        auto rv = Matrix();
        rv.loadIdentity();
        const auto s = std::sqrt(pow(sx, 2) + pow(sy, 2) + pow(sz, 2)); // normalize s axis
        rv[1]        = sx / s;
        rv[5]        = sy / s;
        rv[9]        = sz / s;
        const auto r = std::sqrt(pow(rx, 2) + pow(ry, 2) + pow(rz, 2)); // normalize r axis
        rv[0]        = rx / r;
        rv[4]        = ry / r;
        rv[8]        = rz / r;
        const auto t = std::sqrt(pow(tx, 2) + pow(ty, 2) + pow(tz, 2)); // normalize t axis
        rv[2]        = tx / t;
        rv[6]        = ty / t;
        rv[10]       = tz / t;

        return rv * tv;
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
        return t;
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
        t[0]  = pow(l, 2) + (1 - pow(l, 2)) * cosT;
        t[1]  = l * m * (1 - cosT) - n * sinT;
        t[2]  = l * n * (1 - cosT) + m * sinT;
        t[4]  = l * m * (1 - cosT) + n * sinT;
        t[5]  = pow(m, 2) + (1 - pow(m, 2)) * cosT;
        t[6]  = m * n * (1 - cosT) - l * sinT;
        t[8]  = l * n * (1 - cosT) - m * sinT;
        t[9]  = m * n * (1 - cosT) + l * sinT;
        t[10] = pow(n, 2) + (1 - pow(n, 2)) * cosT;
        return t;
    }

    // orthogonal projection
    static auto orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) -> Matrix {
        Matrix t;
        t.loadIdentity();
        const auto dx = right - left, dy = top - bottom, dz = zFar - zNear;
        if(dx == 0.0f || dy == 0.0f || dz == 0.0f) return t;
        // normalize * move to origin
        t[0]  = 2.0f / dx;
        t[5]  = 2.0f / dy;
        t[10] = -2.0f / dz;
        t[12] = -(right + left) / dx;
        t[13] = -(top + bottom) / dy;
        t[14] = -(zFar - zNear) / dz;
        return t;
    }
};