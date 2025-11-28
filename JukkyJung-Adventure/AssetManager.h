#pragma once
#include "common.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

/**
 * @class AssetManager
 * @brief A template-based singleton class for managing game assets.
 *
 * This class is responsible for loading, storing, and providing access to assets
 * like textures, fonts, and sounds. It ensures that each asset is loaded only once
 * and can be easily retrieved by its file path.
 *
 * @tparam T The type of the asset to be managed (e.g., sf::Texture, sf::Font).
 */
template <typename T>
class AssetManager {
public:
    /**
     * @brief Provides access to the single instance of the AssetManager.
     * @return A reference to the AssetManager instance.
     */
    static AssetManager& getInstance() {
        static AssetManager instance;
        return instance;
    }

    /**
     * @brief Retrieves an asset by its file path.
     * If the asset is not already loaded, it will be loaded from the file.
     * @param filename The file path of the asset.
     * @return A pointer to the loaded asset.
     * @throws std::runtime_error if the asset fails to load.
     */
    T* get(const std::string& filename) {
        if (assets.find(filename) == assets.end()) {
            auto asset = std::make_unique<T>();
            if (!asset->loadFromFile(filename)) {
                throw std::runtime_error("Failed to load asset: " + filename);
            }
            assets[filename] = std::move(asset);
        }
        return assets[filename].get();
    }
    ~AssetManager() = default;
private:
    AssetManager() = default;
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    std::unordered_map<std::string, std::unique_ptr<T>> assets; ///< A map to store the loaded assets.
};
