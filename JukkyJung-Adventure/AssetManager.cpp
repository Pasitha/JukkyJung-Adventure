#include "AssetManager.h"

template <typename AssetType>
AssetType* AssetManager<AssetType>::Load(const std::string& filename) {
    auto asset = std::make_unique<AssetType>();
    if (!asset->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load asset from " + filename);
    }
    auto assetPtr = asset.get();
    assetPool[filename] = std::move(asset);
    return assetPtr;
}

template <typename AssetType>
AssetType& AssetManager<AssetType>::Get(const std::string& filename) {
    auto it = assets_.find(filename);
    if (it != assets_.end()) {
        return *(it->second);
    }
    else {
        throw std::runtime_error("Asset not found: " + filename);
    }
}

SpriteAnimation* AssetManager<SpriteAnimation>::Load(const std::string& filename, sf::Vector2i frameSize, int rowCount) {
    std::unique_ptr asset = std::make_unique<SpriteAnimation>();
    asset->loadSpriteSheet(filename, frameSize, rowCount);

    auto assetPtr = asset.get();
    assetPool[filename] = std::move(asset);
    return assetPtr;
}

SpriteAnimation& AssetManager<SpriteAnimation>::Get(const std::string& filename) {
    auto it = assetPool.find(filename);
    if (it != assetPool.end()) {
        return *(it->second);
    }
    else {
        throw std::runtime_error("Asset not found: " + filename);
    }
}
