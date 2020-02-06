#ifndef PROJETPROGAVANCEE_COLOR_HPP
#define PROJETPROGAVANCEE_COLOR_HPP

#include <array>

class Color {
public:
    Color();
    Color(const Color& copy);
    Color(Color&& move) noexcept;
    explicit Color(uint8_t v);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    Color& operator=(const Color& copy) {
        if (this == &copy) {
            return *this;
        }

        data[0] = copy.data[0];
        data[1] = copy.data[1];
        data[2] = copy.data[2];
        data[3] = copy.data[3];
        return *this;
    }

    uint8_t r() const {
        return data[0];
    }
    void r(uint8_t r) {
        data[0] = r;
    }

    uint8_t g() const {
        return data[1];
    }
    void g(uint8_t g) {
        data[1] = g;
    }

    uint8_t b() const {
        return data[2];
    }
    void b(uint8_t b) {
        data[2] = b;
    }

    uint8_t a() const {
        return data[3];
    }
    void a(uint8_t a) {
        data[3] = a;
    }

private:
    std::array<uint8_t, 4> data;
};

#endif //PROJETPROGAVANCEE_COLOR_HPP
