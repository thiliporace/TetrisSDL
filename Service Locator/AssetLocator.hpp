//
//  AssetLocator.hpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 24/08/25.
//

#ifndef AssetLocator_hpp
#define AssetLocator_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class IAssetService {
public:
    virtual ~IAssetService() {}
    virtual SDL_Texture* getTexture(const std::string& assetPath) = 0;
};

class AssetService : public IAssetService {
public:
    AssetService(SDL_Renderer* renderer);
    ~AssetService();
    virtual SDL_Texture* getTexture(const std::string& assetPath) override;

private:
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> textures;
};

class NullAssetService : public IAssetService {
public:
    virtual SDL_Texture* getTexture(const std::string& assetPath) override {
        return nullptr;
    }
};

class Locator {
public:
    static void initialize();
    static IAssetService& getAssetService();
    static void provide(IAssetService* service);

private:
    static IAssetService* service_;
    static NullAssetService nullService_;
};

#endif /* AssetLocator_hpp */
