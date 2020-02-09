#ifndef PROJETPROGAVANCEE_SETTINGS_HPP
#define PROJETPROGAVANCEE_SETTINGS_HPP

#include <string>
#include <unordered_map>
#include <variant>

class Settings {
public:
    static Settings& getInstance() {
        static Settings instance;
        return instance;
    }

    Settings(const Settings&) = delete;
    void operator=(const Settings&) = delete;

public:
    template <class T>
    const T& getParameter(const std::string& parameter) {
        return std::get<T>(settings[parameter]);
    }

private:
    Settings() {
        loadSettings();
    };

    void loadSettings() {
        settings.insert({"window_width", 1280});
        settings.insert({"window_height", 720});
    }

private:
    std::unordered_map<std::string, std::variant<int>> settings;
};

#endif //PROJETPROGAVANCEE_SETTINGS_HPP
