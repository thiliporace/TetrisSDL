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

class SdlManagerProtocol{
public:
    const virtual void initializeSDL() = 0;
    const virtual void initializeSDLWindow() = 0;
    const virtual void initializeSDLRenderer() = 0;
    
    const virtual SDL_Renderer* getRenderer() = 0;
    const virtual SDL_Window* getWindow() = 0;
    
    ~SdlManagerProtocol() {};
};

class SdlManager: public SdlManagerProtocol{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    static SdlManager* instance;
    
    SdlManager();
    
    SdlManager(const SdlManager& obj) = delete;
    
public:
    static SdlManager* getInstance();
    
    const void initializeSDL() override;
    const void initializeSDLWindow() override;
    const void initializeSDLRenderer() override;
    
    SDL_Renderer* getRenderer() override;
    SDL_Window* getWindow() override;
    
    ~SdlManager();
};


#endif /* SdlManager_hpp */
