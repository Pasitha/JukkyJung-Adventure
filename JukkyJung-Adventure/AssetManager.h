#pragma once
#include "common.h"

template <typename AssetType>
class AssetManager {
public:
    AssetType* Load(const std::string& filename);
    AssetType& Get(const std::string& filename);

private:
    std::unordered_map<std::string, std::unique_ptr<AssetType>> assets_;
};

template <>
class AssetManager<SpriteAnimation> {
public:
    SpriteAnimation* Load(const std::string& filename, const std::vector<sf::IntRect>& frames, float frameDuration);
    SpriteAnimation& Get(const std::string& filename);

private:
    std::unordered_map<std::string, std::unique_ptr<SpriteAnimation>> assets_;
};
