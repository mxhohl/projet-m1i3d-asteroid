#ifndef PROJETPROGAVANCEE_MAT3_HPP
#define PROJETPROGAVANCEE_MAT3_HPP

#include <array>
#include "Vec2.hpp"

template <class T>
class Mat3 {
public:
    Mat3() : data(0) {}
    explicit Mat3(T v) : Mat3(v, v, v, v, v, v, v, v, v) {}
    Mat3(T v11, T v21, T v31, T v12, T v22, T v32, T v13, T v23, T v33)
        : data{v11, v21, v31,
               v12, v22, v32,
               v13, v23, v33} {}

    T& operator()(size_t i, size_t j) {
        return data[j * 3 + i];
    }

    const T& operator()(size_t i, size_t j) const {
        return data[j * 3 + i];
    }

    friend std::ostream& operator<<(std::ostream& s, const Mat3<T>& mat) {
        s << std::string("(");
        for (int i = 0; i < 3; ++i) {
            if (i != 0) {
                s << std::string("; ");
            }
            for (int j = 0; j < 3; ++j) {
                if (j != 0) {
                    s << std::string(", ");
                }
                s << mat.data[j * 3 + i];
            }
        }
        s << std::string(")");
        return s;
    }

    static Mat3<T> identity() {
        return Mat3(1, 0, 0,
                    0, 1, 0,
                    0, 0, 1);
    }

    static Mat3<T> translation(const Vec2<T>& translation) {
        return Mat3f(1, 0, 0,
                     0, 1, 0,
                     translation.x(), translation.y(), 1);
    }

    static Mat3<T> scale(const Vec2<T>& scale) {
        return Mat3f(scale.x(), 0, 0,
                     0, scale.y(), 0,
                     0, 0, 1);
    }

    static Mat3<T> rotation(float rotation) {
        const float cos = std::cos(rotation);
        const float sin = std::sin(rotation);
        return Mat3f(cos, sin, 0,
                     -sin, cos, 0,
                     0, 0, 1);
    }

    void transpose() {
        std::swap(data[1], data[3]);
        std::swap(data[2], data[6]);
        std::swap(data[5], data[7]);
    }

    Mat3<T> transposed() const {
        Mat3 mat(*this);
        mat.transpose();
        return mat;
    }

    friend Mat3<T> operator+(const Mat3<T>& left, const Mat3<T>& right) {
        Mat3 mat;
        for (size_t i = 0; i < 9; ++i) {
            mat.data[i] = left.data[i] + right.data[i];
        }
    }

    template <class U>
    friend Mat3<T> operator*(const Mat3<T>& left, U right) {
        Mat3 mat;
        for (size_t i = 0; i < 9; ++i) {
            mat.data[i] = left.data[i] * right;
        }
    }

    template <class U>
    friend Mat3<T> operator*(T left, const Mat3<T>& right) {
        Mat3 mat;
        for (size_t i = 0; i < 9; ++i) {
            mat.data[i] = left * right.data[i];
        }
    }

    template <class U>
    friend Mat3<T> operator*(const Mat3<T>& left, const Mat3<U>& right) {
        Mat3 mat(0);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    mat.data[j * 3 + i] +=
                            left.data[j * 3 + k] * right.data[k * 3 + i];
                }
            }
        }
        return mat;
    }

    Vec2f transformPoint(const Vec2f& point) const {
        float x = point.x() * data[0] + point.y() * data[3] + data[6];
        float y = point.x() * data[1] + point.y() * data[4] + data[7];
        float w = point.x() * data[2] + point.y() * data[5] + data[8];
        return Vec2f(x / w, y / w);
    }

private:
    std::array<T, 9> data;
};

using Mat3f = Mat3<float>;

#endif //PROJETPROGAVANCEE_MAT3_HPP
