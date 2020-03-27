#ifndef PROJETPROGAVANCEE_UTILS_HPP
#define PROJETPROGAVANCEE_UTILS_HPP

#include <cmath>
#include <sstream>
#include <iomanip>

#ifndef M_PI
constexpr float M_PI = 3.14159265358979323846f;
#endif

inline std::string toStringPrefixed(int val) {
    std::ostringstream oss;
    oss << std::setw(5) << std::setfill('0') << val;
    return oss.str();
}

#endif //PROJETPROGAVANCEE_UTILS_HPP
