#include "Engine/Types/Color.hpp"

using namespace engine;

Color::Color() : Color(0) {}

Color::Color(const Color& copy) = default;

Color::Color(Color&& move) noexcept = default;

Color::Color(uint8_t v) : Color(v, v, v) {}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
    data{r, g, b, a} {}
