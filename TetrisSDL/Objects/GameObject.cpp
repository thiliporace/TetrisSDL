//
//  GameObject.cpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#include "GameObject.hpp"
#include "SdlManager.hpp"

#include <stdio.h>
#include <iostream>
#include <SDL2_image/SDL_image.h>

using namespace std;

GameObject::GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const std::string& assetName, float xSpeed, float ySpeed, float rotation) : currentXSpeed(xSpeed), currentYSpeed(ySpeed), isAlive(true), rotation(rotation) {
    SdlManager* sdlManager = SdlManager::getInstance();
    
    spriteTexture = nullptr;
    
    sprite = IMG_Load(assetName.c_str());
    
    if (!sprite){
        cout << "Error Surface: " << SDL_GetError() << endl;
        return;
    }
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite);
    
    if (!spriteTexture){
        cout << "Error Texture: " << SDL_GetError() << endl;
        return;
    }
    
    SDL_FreeSurface(sprite);
    
    int wPosition = static_cast<int>(position.w);
    int hPosition = static_cast<int>(position.h);
    
    SDL_QueryTexture(spriteTexture, NULL, NULL, &wPosition, &hPosition); //Conecta textura com posicao
    
    position.x = initialXPos;
    position.y = initialYPos;
    
    width = objectWidth;
    height = objectHeight;
    
    position.w = width;
    position.h = height;
}

void GameObject::render(SDL_Renderer* renderer){
    SDL_RenderCopyExF(renderer, spriteTexture, NULL, &position, rotation, NULL, SDL_FLIP_NONE);
}

GameObject::~GameObject(){
    if (spriteTexture) {
        SDL_DestroyTexture(spriteTexture);
        spriteTexture = nullptr;
    }
}

SDL_Texture* GameObject::getTexture(){
    return spriteTexture;
}

bool GameObject::getIsAlive(){
    return isAlive;
}

void GameObject::setIsAlive(bool b){
    isAlive = b;
}

double GameObject::degreesToRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}
