#ifndef PROJETPROGAVANCEE_UTILS_HPP
#define PROJETPROGAVANCEE_UTILS_HPP

#include <cmath>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <fstream>

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
        size_t size;
        buffer.resize(16);
        if ((size = std::strftime(buffer.data(), buffer.size(), format.c_str(), &tm))) {
            buffer.resize(size);
            return buffer;
        }
    }
    throw std::runtime_error("Failed to get current date as string");
}

inline bool fileExists(const std::string& name) {
    std::ifstream iFile(name);
    return iFile.is_open();
}

template <class... Args>
inline std::string sstr(Args&&... args) {
    std::ostringstream sstr;
    sstr << std::dec;
    (sstr << ... << args);
    return sstr.str();
}

#endif //PROJETPROGAVANCEE_UTILS_HPP
