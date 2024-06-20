#include "FileManager.h"

// Initialize static variables
std::vector<std::string> FileManager::missingFiles;
std::unordered_map<std::string, sf::Image> FileManager::imageCache;
std::unordered_map<std::string, sf::Texture> FileManager::textureCache;
std::unordered_map<std::string, sf::Font> FileManager::fontCache;
std::unordered_map<std::string, sf::SoundBuffer> FileManager::soundBufferCache;
std::unordered_map<std::string, sf::Music> FileManager::musicCache;

// Template function to get the cache based on resource type
template <typename T> std::unordered_map<std::string, T>& FileManager::GetCache() {
    // Determine the cache based on the resource type
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
template <typename T>
bool FileManager::LoadFromFile(T& resource, const std::string& fileName) {
    // Check if the resource is already in the cache
    auto& cache = GetCache<T>();

    auto it = cache.find(fileName);
    if (it != cache.end()) {
        // Use the cached resource if available
        resource = it->second;
        return true;
    }
    else {
        // Load the resource from file
        if (!resource.loadFromFile(fileName)) {
            // Throw an exception on loading failure
            throw std::runtime_error("Failed to load file: " + fileName);
            return false;
        }
        else {
            // If loading is successful, add it to the cache
            cache[fileName] = resource;
            return true;
        }
    }
}

// Explicit template instantiations for different resource types
template bool FileManager::LoadFromFile<sf::Image>(sf::Image& resource, const std::string& fileName);
template bool FileManager::LoadFromFile<sf::Texture>(sf::Texture& resource, const std::string& fileName);
template bool FileManager::LoadFromFile<sf::Font>(sf::Font& resource, const std::string& fileName);
template bool FileManager::LoadFromFile<sf::SoundBuffer>(sf::SoundBuffer& resource, const std::string& fileName);

// Specialization for sf::Music
template<>
bool FileManager::LoadFromFile<sf::Music>(sf::Music& resource, const std::string& fileName) {
    // Use openFromFile for sf::Music
    if (!resource.openFromFile(fileName)) {
        // Log a loading failure if unsuccessful
        LogLoadingFailure(fileName);
        return false;
    }
    return true;
}

// Template function to load a resource from a file asynchronously
template<typename T>
std::future<bool> FileManager::LoadAsync(const std::string& fileName) {
    std::promise<bool> promise;
    auto future = promise.get_future();
    std::thread(&FileManager::LoadAsync<T>, std::ref(GetCache<T>()[fileName]), fileName, std::move(promise)).detach();
    return future;
}

// Helper function for asynchronous loading
template<typename T>
void FileManager::LoadAsync(T& resource, const std::string& fileName, std::promise<bool>& promise) {
    bool success = LoadFromFile(resource, fileName);
    promise.set_value(success);
}

std::vector<std::vector<std::string>> FileManager::ParseCSV(const std::string& fileName) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(fileName); // Open file
    if (!file.is_open()) {
		// Throw an exception on loading failure
		throw std::runtime_error("Failed to load file: " + fileName);
    }

    std::string line;
    while (std::getline(file, line)) { // Read each line from the file
        data.push_back(SplitLine(line, ',')); // Split the line into tokens and add to data
    }

    file.close(); // Close the file
    return data;
}

// Function to clear the entire cache
void FileManager::ClearCache() {
    imageCache.clear();
    textureCache.clear();
    fontCache.clear();
    soundBufferCache.clear();
    musicCache.clear();
}

// Explicit template instantiations for clearing cache of different resource types
template void FileManager::ClearCache<sf::Image>();
template void FileManager::ClearCache<sf::Texture>();
template void FileManager::ClearCache<sf::Font>();
template void FileManager::ClearCache<sf::SoundBuffer>();
template void FileManager::ClearCache<sf::Music>();

// Template function to clear the cache for a specific resource type
template<typename T>
void FileManager::ClearCache() {
    ClearCacheForType(GetCache<T>());
}

// Helper function to split a line into tokens based on a delimiter
std::vector<std::string> FileManager::SplitLine(const std::string& line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    // Extract tokens based on the delimiter
    while (std::getline(ss, token, delimiter)) {
        // Handle potential quotes within tokens
        if (token.front() == '"' && token.back() == '"') {
            // Remove leading and trailing quotes if present
            token = token.substr(1, token.size() - 2);
        }
        tokens.push_back(token);
    }

    // Handle the last token (if no trailing delimiter)
    if (!ss.eof()) {
        tokens.push_back(ss.str());
    }

    return tokens;
}

// Helper function to clear cache for a specific resource type
template<typename T>
void FileManager::ClearCacheForType(std::unordered_map<std::string, T>& cache) {
    cache.clear();
}

// Function to get a list of missing files
bool FileManager::getMissingFileList(std::string& fileList) {
    if (missingFiles.empty()) {
        return false;
    }
    else {
        // Concatenate missing file names into a string
        for (auto it : missingFiles) {
            fileList += it + '\n';
        }
        return true;
    }
}

// Function to check if any file is missing
bool FileManager::IsAnyFileMissing() {
    // Return true if there are missing files
    return !missingFiles.empty();
}

// Function to log a loading failure with the filename
void FileManager::LogLoadingFailure(const std::string& fileName) {
#ifdef _DEBUG
    // Print an error message to the standard error stream
    std::cerr << "Failed to load file: " << fileName << std::endl;
#endif
    // Add the filename to the list of missing files
    missingFiles.push_back(fileName);
}
