//
//  GameObject.hpp
//  Asteroids NDP
//
//  Created by Thiago Liporace on 07/05/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <string.h>
#include <stdio.h>
#include <list>
#include <SDL2/SDL.h>

class GameObject {
private:
    SDL_Surface* sprite;
    
    SDL_Texture* spriteTexture;
    
    float width,height;

protected:
    bool isAlive;

public:
    SDL_FRect position;
    
    double rotation;
    
    float currentXSpeed, currentYSpeed;
    
    GameObject(int initialXPos, int initialYPos, int objectWidth, int objectHeight, const std::string& assetName,
               float xSpeed = 0, float ySpeed = 0, float rotation = 0);
    
    virtual void update(float deltaTime) = 0;
    
    double degreesToRadians(double degrees);
    
    SDL_Texture* getTexture();
    
    bool getIsAlive();
    
    void setIsAlive(bool b);
    
    virtual ~GameObject();
};

#endif /* GameObject_hpp */
