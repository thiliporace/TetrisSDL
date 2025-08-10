//
//  Game.hpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <memory>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Tetronimo.hpp"
#include "StaticImage.hpp"

// Define the dimensions of the game board grid.
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int BLOCK_SIZE = 30; // Size of each block in pixels

class Game {
public:
    Game(SDL_Renderer* renderer);
    ~Game();

    void handleInput(const SDL_Event& event);
    void update(float deltaTime);
    void render();
    bool isGameOver();

private:
    void spawnTetromino();
    bool isValidPosition(const Tetromino& piece, int newX, int newY);
    void lockTetromino();
    void clearLines();
    void generateNextTetromino();

    SDL_Renderer* renderer;
    std::vector<std::vector<int>> board;
    std::unique_ptr<Tetromino> currentTetromino;
    std::unique_ptr<Tetromino> nextTetromino;
    
    std::unique_ptr<StaticImage> border;
    
    std::map<TetrominoType, SDL_Texture*> blockTextures;

    float fallTimer;
    float fallSpeed;
    bool gameOver;
};

#endif /* Game_hpp */
