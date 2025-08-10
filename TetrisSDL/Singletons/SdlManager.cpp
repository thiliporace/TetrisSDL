//
//  SdlManager.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 27/07/25.
//

#include <iostream>
#include "SdlManager.hpp"

using namespace std;

SdlManager* SdlManager::instance = nullptr;

SdlManager::SdlManager() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
    }
}

SdlManager::~SdlManager() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

SdlManager* SdlManager::getInstance() {
    if (instance == nullptr) {
        instance = new SdlManager();
    }
    return instance;
}

SDL_Renderer* SdlManager::getRenderer() {
    return renderer;
}

SDL_Window* SdlManager::getWindow() {
    return window;
}
