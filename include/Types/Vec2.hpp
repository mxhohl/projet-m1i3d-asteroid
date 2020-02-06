#ifndef VEC2_HPP
#define VEC2_HPP

template<class T>
class Vec2 {
public:
    Vec2() : Vec2(0) {}
    Vec2(const Vec2& copy) = default;
    Vec2(Vec2&& move) = default;
    explicit Vec2(T v) : Vec2(v, v) {}
    Vec2(T x, T y) : x(x), y(y) {}
    Vec2(std::initializer_list<T> params) {
        /* TODO */
    }

    /* TODO: operators, getters, setters */

private:
    T x;
    T y;
};

using Vec2f = Vec2<float>;

#endif // VEC2_HPP
