#include "FileManager.h"

// Initialize static variables
std::vector<std::string> FileManager::missingFiles;
std::unordered_map<std::string, sf::Image> FileManager::imageCache;
std::unordered_map<std::string, sf::Texture> FileManager::textureCache;
std::unordered_map<std::string, sf::Font> FileManager::fontCache;
std::unordered_map<std::string, sf::SoundBuffer> FileManager::soundBufferCache;
std::unordered_map<std::string, sf::Music> FileManager::musicCache;

// Template function to get the cache based on resource type
template <typename T>
std::unordered_map<std::string, T>& FileManager::GetCache() {
    if constexpr (std::is_same_v<T, sf::Image>) {
        return imageCache;
    }
    else if constexpr (std::is_same_v<T, sf::Texture>) {
        return textureCache;
    }
    else if constexpr (std::is_same_v<T, sf::Font>) {
        return fontCache;
    }
    else if constexpr (std::is_same_v<T, sf::SoundBuffer>) {
        return soundBufferCache;
    }
    else if constexpr (std::is_same_v<T, sf::Music>) {
        return musicCache;
    }
    else {
        // Handle unsupported types
        static_assert(always_false<T>::value, "Unsupported resource type");
    }
}

// Template function to load a resource from a file
template <typename T> void FileManager::LoadFromFile(T& resource, const std::string& fileName) {
    // Check if the resource is already in the cache
    auto& cache = GetCache<T>();

    auto it = cache.find(fileName);
    if (it != cache.end()) {
        resource = it->second;
    }
    else {
        // Load the resource from file
        if (!resource.loadFromFile(fileName)) {
            LogLoadingFailure(fileName);
        }
        else {
            // If loading is successful, add it to the cache
            cache[fileName] = resource;
        }
    }
}

// Explicit template instantiations for different resource types
template void FileManager::LoadFromFile<sf::Image>(sf::Image& resource, const std::string& fileName);
template void FileManager::LoadFromFile<sf::Texture>(sf::Texture& resource, const std::string& fileName);
template void FileManager::LoadFromFile<sf::Font>(sf::Font& resource, const std::string& fileName);
template void FileManager::LoadFromFile<sf::SoundBuffer>(sf::SoundBuffer& resource, const std::string& fileName);

// Specialization for sf::Music
template<> void FileManager::LoadFromFile<sf::Music>(sf::Music& resource, const std::string& fileName) {
    // Use openFromFile for sf::Music
    if (!resource.openFromFile(fileName)) {
        LogLoadingFailure(fileName);
    }
}

// Function to get a list of missing files
bool FileManager::getMissingFileList(std::string& fileList) {
    if (missingFiles.empty()) {
        return false;
    }
    else {
        for (auto it : missingFiles) {
            fileList += it + '\n';
        }
        return true;
    }
}

// Function to check if any file is missing
bool FileManager::IsAnyFileMissing() {
    return !missingFiles.empty();
}

// Function to log a loading failure with the filename
void FileManager::LogLoadingFailure(const std::string& fileName) {
    std::cerr << "Failed to load file: " << fileName << std::endl;
    missingFiles.push_back(fileName);
}
