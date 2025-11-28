#pragma once
#include "common.h"
#include <unordered_map>

class Settings {
public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

    template<typename T>
    T get(const std::string& key) const;

    template<typename T>
    void set(const std::string& key, const T& value);

private:
    std::unordered_map<std::string, std::string> values;
};
