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

GameObject::GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const std::string& assetName, float xSpeed, float ySpeed, float rotation) : currentXSpeed(xSpeed), currentYSpeed(ySpeed), rotation(rotation) {
    spriteTexture = Locator::getAssetService().getTexture(assetName);
    
    if (spriteTexture) {
        int wPosition = 0;
        int hPosition = 0;
        SDL_QueryTexture(spriteTexture, NULL, NULL, &wPosition, &hPosition);
    } 
    else {
        cout << "GameObject received null texture for asset: " << assetName << endl;
    }
    
    position.x = initialXPos;
    position.y = initialYPos;
}

void GameObject::render(SDL_Renderer* renderer){
    SDL_RenderCopyExF(renderer, spriteTexture, NULL, &position, rotation, NULL, SDL_FLIP_NONE);
}

GameObject::~GameObject(){}

SDL_Texture* GameObject::getTexture(){
    return spriteTexture;
}
