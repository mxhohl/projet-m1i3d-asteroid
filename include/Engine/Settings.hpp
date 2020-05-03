#ifndef PROJETPROGAVANCEE_SETTINGS_HPP
#define PROJETPROGAVANCEE_SETTINGS_HPP

#include <string>
#include <unordered_map>
#include <variant>

namespace engine {

class Settings {
public:
    static Settings &getInstance() {
        static Settings instance;
        return instance;
    }

    Settings(const Settings &) = delete;

    void operator=(const Settings &) = delete;

public:
    template<class T>
    const T &getParameter(const std::string &parameter) const {
        return std::get<T>(settings.at(parameter));
    }

private:
    Settings() {
        loadSettings();
    };

    void loadSettings() {
        settings.insert({"window_width", 1280});
        settings.insert({"window_height", 720});
        settings.insert({"seed", 546687u});
        settings.insert({"init_asteroid_count", 10u});
    }

private:
    std::unordered_map<std::string, std::variant<int, unsigned int>> settings;
};

}

#endif //PROJETPROGAVANCEE_SETTINGS_HPP
