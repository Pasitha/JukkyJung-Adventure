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

    // Helper function to split a line into tokens based on a delimiter
    static std::vector<std::string> SplitLine(const std::string& line, char delimiter);

    // Helper function to clear cache for a specific resource type
    template<typename T>
    static void ClearCacheForType(std::unordered_map<std::string, T>& cache);

    // Helper function for asynchronous loading
    template<typename T>
    static void LoadAsync(T& resource, const std::string& fileName, std::promise<bool>& promise);

public:
    // Delete copy constructor and assignment operator to prevent duplication
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    // Template function to load a resource from a file
    template<typename T> 
    static bool LoadFromFile(T& resource, const std::string& fileName);

    // Template function to load a resource from a file asynchronously
    template<typename T>
    static std::future<bool> LoadAsync(const std::string& fileName);

    // Function to parse a CSV file and return a 2D vector of strings
    static std::vector<std::vector<std::string>> ParseCSV(const std::string& fileName);

    // Function to clear the entire cache
    static void ClearCache();

    // Template function to clear the cache for a specific resource type
    template<typename T>
    static void ClearCache();

    // Function to get a list of missing files
    static bool getMissingFileList(std::string& fileList);

    // Function to check if any file is missing
    inline static bool IsAnyFileMissing();

    // Function to log a loading failure with the filename
    static void LogLoadingFailure(const std::string& fileName);
};
