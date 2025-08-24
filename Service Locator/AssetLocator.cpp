//
//  AssetLocator.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 24/08/25.
//

#include "AssetLocator.hpp"

IAssetService* Locator::service_ = nullptr;
NullAssetService Locator::nullService_;

void Locator::initialize() {
    service_ = &nullService_;
}

IAssetService& Locator::getAssetService() {
    return *service_;
}

void Locator::provide(IAssetService* service) {
    if (service == nullptr) {
        service_ = &nullService_;
    } else {
        service_ = service;
    }
}

AssetService::AssetService(SDL_Renderer* renderer) : renderer(renderer) {}

AssetService::~AssetService() {
    for (auto const& [key, val] : textures) {
        if (val) {
            SDL_DestroyTexture(val);
        }
    }
    textures.clear();
    std::cout << "AssetService destroyed and textures cleared." << std::endl;
}

SDL_Texture* AssetService::getTexture(const std::string& assetPath) {
    auto it = textures.find(assetPath);
    if (it != textures.end()) {
        return it->second;
    }

    SDL_Texture* newTexture = IMG_LoadTexture(renderer, assetPath.c_str());
    if (newTexture == nullptr) {
        std::cout << "Failed to load texture " << assetPath << "! Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    textures[assetPath] = newTexture;
    return newTexture;
}
