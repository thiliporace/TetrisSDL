//
//  SdlManager.hpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 27/07/25.
//

#ifndef SdlManager_hpp
#define SdlManager_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class SdlManager {
private:
    SdlManager();
    ~SdlManager();
    static SdlManager* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    static SdlManager* getInstance();
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
};


#endif /* SdlManager_hpp */
