#ifndef VEC2_HPP
#define VEC2_HPP

#include <array>
#include <cmath>

template<class T>
class Vec2 {
public:
    Vec2() : Vec2(0) {}
    Vec2(const Vec2& copy) = default;
    Vec2(Vec2&& move) noexcept = default;
    explicit Vec2(T v) : Vec2(v, v) {}
    Vec2(T x, T y) : data{x, y} {}
    Vec2(std::initializer_list<T> params) {
        auto param = params.begin();
        data[0] = *param++;
        data[1] = *param;
    }

    Vec2<T>& operator=(const Vec2<T>& copy) {
        if (this == &copy) {
            return *this;
        }

        data[0] = copy.data[0];
        data[1] = copy.data[1];
        return *this;
    }

    T x() const {
        return data[0];
    }

    void x(T x) {
        data[0] = x;
    }

    T y() const {
        return data[1];
    }

    void y(T y) {
        data[1] = y;
    }

    T sqrLength() const {
        return data[0] * data[0] + data[1] * data[1];
    }

    T length() const {
        return sqrt(sqrLength());
    }

    void normalize() {
        const auto len = length();
        data[0] /= len;
        data[1] /= len;
    }

    Vec2<T> normalized() const {
        Vec2 vec(*this);
        vec.normalize();
        return vec;
    }

    T& operator[](size_t i) {
        return data[i];
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    friend std::ostream& operator<< (std::ostream& s, const Vec2<T>& v) {
        s << std::string("(") << v.data[0] << ", " << v.data[1] << ")";
        return s;
    }

    friend Vec2<T> operator+(const Vec2<T>& right) {
        return Vec2(
            +right.data[0],
            +right.data[1]
        );
    }

    friend Vec2<T> operator-(const Vec2<T>& right) {
        return Vec2(
                -right.data[0],
                -right.data[1]
        );
    }

    template <class U>
    friend auto operator+(const Vec2<T>& left, const Vec2<U>& right) {
        return Vec2(
            left.data[0] + right.data[0],
            left.data[1] + right.data[1]
        );
    }

    template <class U>
    friend auto operator-(const Vec2<T>& left, const Vec2<U>& right) {
        return Vec2(
                left.data[0] - right.data[0],
                left.data[1] - right.data[1]
        );
    }

    template <class U>
    friend auto operator*(const Vec2<T>& left, U right) {
        return Vec2(
                left.data[0] * right,
                left.data[1] * right
        );
    }

    template <class U>
    friend auto operator*(U left, const Vec2<T>& right) {
        return Vec2(
                left * right.data[0],
                left * right.data[1]
        );
    }

    template <class U>
    friend auto operator/(const Vec2<T>& left, U right) {
        return Vec2(
                left.data[0] / right,
                left.data[1] / right
        );
    }

    template <class U>
    friend auto operator+=(Vec2<T>& left, const Vec2<U>& right) {
        left.data[0] += right.data[0];
        left.data[1] += right.data[1];
    }

    template <class U>
    friend auto operator-=(Vec2<T>& left, const Vec2<U>& right) {
        left.data[0] -= right.data[0];
        left.data[1] -= right.data[1];
    }

    template <class U>
    friend auto operator*=(Vec2<T>& left, U right) {
        left.data[0] *= right;
        left.data[1] *= right;
    }

    template <class U>
    friend auto operator/=(Vec2<T>& left, U right) {
        left.data[0] /= right;
        left.data[1] /= right;
    }

    template <class U>
    friend auto operator==(const Vec2<T>& left, const Vec2<U>& right) {
        return left.data[0] == right.data[0]
            && left.data[1] == right.data[1];
    }

    template <class U>
    friend auto operator!=(const Vec2<T>& left, const Vec2<U>& right) {
        return left.data[0] != right.data[0]
            || left.data[1] != right.data[1];
    }


private:
    std::array<T, 2> data;
};

using Vec2f = Vec2<float>;

#endif // VEC2_HPP
