//
//  StaticImage.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#include "StaticImage.hpp"
#include <iostream>

StaticImage::StaticImage(SDL_Renderer* renderer, const std::string& assetPath, int x, int y) {
    texture = nullptr;

    SDL_Surface* surface = IMG_Load(assetPath.c_str());
    if (!surface) {
        std::cout << "Error creating surface for " << assetPath << ": " << IMG_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cout << "Error creating texture from " << assetPath << ": " << SDL_GetError() << std::endl;
    }

    destinationRect.x = x;
    destinationRect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &destinationRect.w, &destinationRect.h);

    SDL_FreeSurface(surface);
}

StaticImage::~StaticImage() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void StaticImage::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
    }
}
