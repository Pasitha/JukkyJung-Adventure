#pragma once
#include "common.h"

// Define a struct to always evaluate to false, used for static assertions
template <class T>
struct always_false : std::false_type {};

// FileManager class for handling resource loading and caching
class FileManager {
private:
    FileManager() {}

    // Template function to get the cache based on resource type
    template <typename T> static std::unordered_map<std::string, T>& GetCache();

    // Vector to store missing files during resource loading
    static std::vector<std::string> missingFiles;

    // Caches for different resource types
    static std::unordered_map<std::string, sf::Image> imageCache;
    static std::unordered_map<std::string, sf::Texture> textureCache;
    static std::unordered_map<std::string, sf::Font> fontCache;
    static std::unordered_map<std::string, sf::SoundBuffer> soundBufferCache;
    static std::unordered_map<std::string, sf::Music> musicCache;

public:
    // Delete copy constructor and assignment operator to prevent duplication
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    // Template function to load a resource from a file
    template<typename T> 
    static void LoadFromFile(T& resource, const std::string& fileName);

    // Function to get a list of missing files
    static bool getMissingFileList(std::string& fileList);

    // Function to check if any file is missing
    inline static bool IsAnyFileMissing();

    // Function to log a loading failure with the filename
    static void LogLoadingFailure(const std::string& fileName);
};
