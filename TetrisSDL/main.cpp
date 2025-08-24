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
#include <functional>

#include "SdlManager.hpp"
#include "SdlManager.hpp"
#include "AssetLocator.hpp"
#include "Game.hpp"

using namespace std;

//60 FPS
//const float MS_PER_UPDATE = 0.016;
//240 FPS
const float MS_PER_UPDATE = 0.004;

float getCurrentTime(){
    return SDL_GetTicks() / 1000.0f;
}

int main(){
    //Singleton pra funções comuns do SDL
    SdlManager* sdlManager = SdlManager::getInstance();
    
    SDL_Renderer* renderer = sdlManager->getRenderer();
    
    Locator::initialize();
    auto assetService = std::make_unique<AssetService>(renderer);
    Locator::provide(assetService.get());
    
    std::unique_ptr<Game> game = std::make_unique<Game>(renderer);
    
    SDL_Event event;
    bool quit = false;
    
    double previous = getCurrentTime();
    
    double lag = 0.0;
    double fpsCounter = 0.0;
    
    int renderFrames = 0;
    int updateFrames = 0;
    
    std::function<void(const SDL_Event&)> currentHandleInput;
    std::function<void(float)> currentUpdate;

    auto gameOverUpdate = [](float dt){};
    auto gameOverInput = [](const SDL_Event& e){};

    auto playingUpdate = [&](float dt) {
        game->update(dt);
        if (game->isGameOver()) {
            std::cout << "Game Over!" << std::endl;
            currentUpdate = gameOverUpdate;
            currentHandleInput = gameOverInput;
        }
    };
    
    auto playingInput = [&](const SDL_Event& e) {
        game->handleInput(e);
    };

    currentUpdate = playingUpdate;
    currentHandleInput = playingInput;
    
    while (!quit){
       double current = getCurrentTime();
       double elapsed = current - previous;
       previous = current;
       lag += elapsed;
       fpsCounter += elapsed;
       
       while(SDL_PollEvent(&event) != 0){
           switch(event.type){
               case SDL_QUIT:
                   quit = true;
                   break;
           }
           currentHandleInput(event);
           
       }
       
       //Usando o Game Programming Pattern Update pra manter uma taxa de frames fixa, com um time step fixo e uma renderização variável (como não passamos lag residual pra renderização, em máquinas mais lentas a renderização pode ocorrer menos frequentemente que o update, causando artefatos visuais. Como essa máquina é meio goat 🐐 (bode 🐐) a renderização sempre roda mais rápido (uns 1000fps enquanto o update roda a uma taxa fixa))
       while (lag >= MS_PER_UPDATE){
           currentUpdate(MS_PER_UPDATE);
           updateFrames++;
           lag -= MS_PER_UPDATE;
       }
       
        if (fpsCounter >= 1.0f){
            std::cout << "UPDATE FPS: " << updateFrames << std::endl;
            std::cout << "RENDER FPS: " << renderFrames << std::endl;
            
            updateFrames = 0;
            renderFrames = 0;
            fpsCounter -= 1.0f;
        }
       
       game->render();
       renderFrames++;
   }
    
    return 0;
}
