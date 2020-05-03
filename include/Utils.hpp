#ifndef PROJETPROGAVANCEE_UTILS_HPP
#define PROJETPROGAVANCEE_UTILS_HPP

#include <cmath>
#include <sstream>
#include <iomanip>
#include <chrono>

#ifndef M_PI
constexpr float M_PI = 3.14159265358979323846f;
#endif

inline std::string toStringPrefixed(int val) {
    std::ostringstream oss;
    oss << std::setw(5) << std::setfill('0') << val;
    return oss.str();
}

inline std::string toString(std::chrono::system_clock::time_point t,
                            const std::string& format = "%H:%M:%S") {
    auto as_time_t = std::chrono::system_clock::to_time_t(t);
    struct tm tm{};
    if (::gmtime_r(&as_time_t, &tm)) {
        std::string buffer;
        buffer.resize(16);
        if (std::strftime(buffer.data(), buffer.size(), format.c_str(), &tm)) {
            return buffer;
        }
    }
    throw std::runtime_error("Failed to get current date as string");
}

#endif //PROJETPROGAVANCEE_UTILS_HPP
