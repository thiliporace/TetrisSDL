//
//  main.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 27/07/25.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <list>

#include "SdlManager.hpp"
#include "GameObject.hpp"

//60 FPS
//const float MS_PER_UPDATE = 0.016;
//240 FPS
const float MS_PER_UPDATE = 0.004;

//Armazena todos os objetos na cena pra atualizar todos de uma vez
std::list<std::shared_ptr<GameObject>> gameObjectsInScene; //Ponteiros inteligentes pra evitar problemas com gerenciamento de mem

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

void update(float deltaTime){
    for (auto& gameObject : gameObjectsInScene){
        gameObject->update(deltaTime);
    }
}

void render(SDL_Renderer* renderer){
    
}

int main(){
    //Singleton pra funções comuns do SDL
    SdlManager* sdlManager = SdlManager::getInstance();
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    
    double lag = 0.0;
    double fpsCounter = 0.0;
    
    int renderFrames = 0;
    int updateFrames = 0;
    
    while (!quit){
       double current = getCurrentTime();
       double elapsed = current - previous;
       previous = current;
       lag += elapsed;
       fpsCounter += elapsed;
       
       while(SDL_PollEvent(&event)){
           switch(event.type){
               case SDL_QUIT:
                   quit = true;
                   break;
           }
           
       }
       
       //Usando o Game Programming Pattern Update pra manter uma taxa de frames fixa, com um time step fixo e uma renderização variável (como não passamos lag residual pra renderização, em máquinas mais lentas a renderização pode ocorrer menos frequentemente que o update, causando artefatos visuais. Como essa máquina é meio goat 🐐 (bode 🐐) a renderização sempre roda mais rápido (uns 1000fps enquanto o update roda a uma taxa fixa))
       while (lag >= MS_PER_UPDATE){
           updateFrames++;
           update(MS_PER_UPDATE);
           lag -= MS_PER_UPDATE;
       }
       
        if (fpsCounter >= 1.0f){
            std::cout << "UPDATE FPS: " << updateFrames << std::endl;
            std::cout << "RENDER FPS: " << renderFrames << std::endl;
            
            updateFrames = 0;
            renderFrames = 0;
            fpsCounter -= 1.0f;
        }
       
       render(renderer);
       renderFrames++;
   }
    
    return 0;
}
