//
//  StaticImage.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#include "StaticImage.hpp"
#include "AssetLocator.hpp"

#include <iostream>

StaticImage::StaticImage(SDL_Renderer* renderer, const std::string& assetPath, int x, int y) {
    texture = Locator::getAssetService().getTexture(assetPath);
    
    destinationRect.x = x;
    destinationRect.y = y;
    
    if (texture) {
        SDL_QueryTexture(texture, NULL, NULL, &destinationRect.w, &destinationRect.h);
    }
}

StaticImage::~StaticImage() {}

void StaticImage::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
    }
}
