#ifndef PROJETPROGAVANCEE_RECT_HPP
#define PROJETPROGAVANCEE_RECT_HPP

#include "Vec2.hpp"

namespace engine {

template<class T>
class Rect {
public:
    Rect() : Rect(0, 0, 0, 0) {}
    Rect(T x, T y, T w, T h) : Rect({x, y}, {w, h}) {}
    Rect(const Vec2<T> &pos, const Vec2<T> &size) :
            pos(pos), wh(size) {}

    template<class U>
    explicit Rect(const Rect<U> &other) : pos(other.pos), wh(other.wh) {}

    const Vec2<T> &position() const { return pos; }

    const Vec2<T> &size() const { return wh; }

    T x() const { return pos.x(); }
    T y() const { return pos.y(); }

    T width() const { return wh.x(); }
    T height() const { return wh.y(); }

    void x(const T &x) { pos.x(x); }
    void y(const T &y) { pos.y(y); }

    void width(const T &width) { wh.x(width); }
    void height(const T &height) { wh.y(height); }

private:
    Vec2<T> pos;
    Vec2<T> wh;
};

using RectF = Rect<float>;
using RectI = Rect<int>;

}

#endif //PROJETPROGAVANCEE_RECT_HPP
