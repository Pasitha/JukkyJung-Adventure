#pragma once
#include "common.h"

// Define a struct to always evaluate to false, used for static assertions
template <class T>
struct always_false : std::false_type {};

// FileManager class for handling resource loading and caching
class FileManager {
private:
    // Private constructor to prevent instantiation
    FileManager() {}

    /**
     * Gets the cache based on the resource type.
     * This template function returns a reference to the appropriate cache for the given resource type.
     * @tparam T The type of the resource.
     * @return A reference to the cache for the resource type.
     */
    template <typename T>
    static std::unordered_map<std::string, T>& GetCache();

    // Vector to store missing files during resource loading
    static std::vector<std::string> missingFiles;

    // Caches for different resource types
    static std::unordered_map<std::string, sf::Image> imageCache;
    static std::unordered_map<std::string, sf::Texture> textureCache;
    static std::unordered_map<std::string, sf::Font> fontCache;
    static std::unordered_map<std::string, sf::SoundBuffer> soundBufferCache;
    static std::unordered_map<std::string, sf::Music> musicCache;

    /**
     * Splits a line into tokens based on a delimiter.
     * This function takes a string line and splits it into tokens using the specified delimiter.
     * @param line The string to split.
     * @param delimiter The character used to split the line into tokens.
     * @return A vector of tokens as strings.
     */
    static std::vector<std::string> SplitLine(const std::string& line, char delimiter);

    /**
     * Clears the cache for a specific resource type.
     * This template function clears the cache for the given resource type.
     * @tparam T The type of the resource.
     * @param cache The cache to be cleared.
     */
    template<typename T>
    static void ClearCacheForType(std::unordered_map<std::string, T>& cache);

    /**
     * Asynchronously loads a resource.
     * This template function loads a resource from a file asynchronously and sets a promise to indicate the result.
     * @tparam T The type of the resource.
     * @param resource The resource to load.
     * @param fileName The name of the file to load the resource from.
     * @param promise A promise to set the result of the loading operation.
     */
    template<typename T>
    static void LoadAsync(T& resource, const std::string& fileName, std::promise<bool>& promise);

public:
    // Delete copy constructor and assignment operator to prevent duplication
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    /**
     * Loads a resource from a file.
     * This template function loads the specified resource from the given file.
     * @tparam T The type of the resource.
     * @param resource The resource to load.
     * @param fileName The name of the file to load the resource from.
     * @return A boolean indicating whether the resource was successfully loaded.
     */
    template<typename T>
    static bool LoadFromFile(T& resource, const std::string& fileName);

    /**
     * Loads a resource from a file asynchronously.
     * This template function loads the specified resource from the given file asynchronously.
     * @tparam T The type of the resource.
     * @param fileName The name of the file to load the resource from.
     * @return A future boolean indicating whether the resource was successfully loaded.
     */
    template<typename T>
    static std::future<bool> LoadAsync(const std::string& fileName);

    /**
     * Parses a CSV file and returns a 2D vector of strings.
     * This function reads the specified CSV file and parses its content into a 2D vector of strings.
     * @param fileName The name of the CSV file to parse.
     * @return A 2D vector of strings representing the parsed CSV data.
     */
    static std::vector<std::vector<std::string>> ParseCSV(const std::string& fileName);

    /**
     * Parses a CSV string into a vector of vectors of strings.
     * Handles basic CSV formatting, including quoted fields and empty values.
     * @param fileName The name of the CSV file to parse.
     * @param delimiter The delimiter character (default: ',').
     * @param quote The quote character (default: '"').
     * @return A vector of vectors of strings representing the parsed CSV data.
     */
    static std::vector<std::vector<std::string>> ParseCSV(const std::string& fileName, char delimiter = ',', char quote = '"');

    /**
     * Clears the entire cache.
     * This function clears the caches for all resource types.
     */
    static void ClearCache();

    /**
     * Clears the cache for a specific resource type.
     * This template function clears the cache for the given resource type.
     * @tparam T The type of the resource.
     */
    template<typename T>
    static void ClearCache();

    /**
     * Gets a list of missing files.
     * This function returns a list of files that were missing during resource loading.
     * @param fileList A reference to a string to store the list of missing files.
     * @return A boolean indicating whether there are any missing files.
     */
    static bool getMissingFileList(std::string& fileList);

    /**
     * Checks if any file is missing.
     * This function checks if there are any files missing during resource loading.
     * @return A boolean indicating whether any file is missing.
     */
    inline static bool IsAnyFileMissing();

    /**
     * Logs a loading failure with the filename.
     * This function logs an error message indicating the failure to load the specified file.
     * @param fileName The name of the file that failed to load.
     */
    static void LogLoadingFailure(const std::string& fileName);
};
