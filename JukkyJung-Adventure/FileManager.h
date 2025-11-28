#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>

class FileManager {
public:
    static std::vector<std::vector<std::string>> ParseCSV(const std::string& fileName, char delimiter = ',');

private:
    static std::vector<std::string> SplitLine(const std::string& line, char delimiter);
};
