//
//  StaticImage.hpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#ifndef StaticImage_hpp
#define StaticImage_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

class StaticImage {
public:
    StaticImage(SDL_Renderer* renderer, const std::string& assetPath, int x, int y);
    ~StaticImage();
    void render(SDL_Renderer* renderer);

private:
    SDL_Texture* texture;
    SDL_Rect destinationRect;
};

#endif /* StaticImage_hpp */
