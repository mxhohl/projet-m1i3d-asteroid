#ifndef PROJETPROGAVANCEE_RECT_HPP
#define PROJETPROGAVANCEE_RECT_HPP

#include "Vec2.hpp"

template <class T>
class Rect {
public:
    Rect() : Rect(0, 0, 0, 0) {}
    Rect(T x, T y, T w, T h) : Rect({x, y}, {w, h}) {}
    Rect(const Vec2<T>& pos, const Vec2<T>& size) :
        Rect(pos, size.x(), size.y()) {}
    Rect(const Vec2<T>& pos, T w, T h) : pos(pos), w(w), h(h) {}

    const Vec2<T>& position() { return pos; }
    const Vec2<T>& size() { return {w, h}; }

    T x() const { return pos.x(); }
    T y() const { return pos.y(); }
    T width() const { return w; }
    T height() const { return h; }

private:
    Vec2<T> pos;
    T w;
    T h;
};

using RectF = Rect<float>;

#endif //PROJETPROGAVANCEE_RECT_HPP
