#include "FileManager.h"

std::vector<std::vector<std::string>> FileManager::ParseCSV(const std::string& fileName, char delimiter) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to load file: " + fileName);
    }

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(SplitLine(line, delimiter));
    }

    file.close();
    return data;
}

std::vector<std::string> FileManager::SplitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
