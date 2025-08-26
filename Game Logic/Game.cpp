//
//  Game.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#include "Game.hpp"
#include <random>
#include <iostream>

SDL_Texture* loadBlockTexture(SDL_Renderer* renderer, const std::string& path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == nullptr) {
        std::cout << "Failed to load texture " << path << "! Error: " << IMG_GetError() << std::endl;
    }
    return newTexture;
}

Game::Game(SDL_Renderer* renderer) : renderer(renderer), fallTimer(0.0f), fallSpeed(0.5f), gameOver(false) {
    board.resize(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0));
    
    border = std::make_unique<StaticImage>(renderer, "border.png", 200, -100);
    
    blockTextures[TetrominoType::I] = loadBlockTexture(renderer, "Tetromino_block1_1.png");
    blockTextures[TetrominoType::O] = loadBlockTexture(renderer, "Tetromino_block1_2.png");
    blockTextures[TetrominoType::T] = loadBlockTexture(renderer, "Tetromino_block1_3.png");
    blockTextures[TetrominoType::L] = loadBlockTexture(renderer, "Tetromino_block1_4.png");
    blockTextures[TetrominoType::J] = loadBlockTexture(renderer, "Tetromino_block1_5.png");
    blockTextures[TetrominoType::S] = loadBlockTexture(renderer, "Tetromino_block1_6.png");
    blockTextures[TetrominoType::Z] = loadBlockTexture(renderer, "Tetromino_block1_7.png");
    
    boardTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE);
    
    updateBoardTexture();
    
    SDL_SetTextureBlendMode(boardTexture, SDL_BLENDMODE_BLEND);

    generateNextTetromino();
    spawnTetromino();
}

Game::~Game() {
    for (auto const& [key, tex] : blockTextures) {
        SDL_DestroyTexture(tex);
    }
    blockTextures.clear();
    
    SDL_DestroyTexture(boardTexture);
}

void Game::updateBoardTexture() {
    SDL_SetRenderTarget(renderer, boardTexture);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (int y = 0; y < BOARD_HEIGHT; ++y) {
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (board[y][x] != 0) {
                TetrominoType type = static_cast<TetrominoType>(board[y][x] - 1);
                SDL_Texture* tex = blockTextures[type];
                SDL_Rect blockRect = { x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
                SDL_RenderCopy(renderer, tex, NULL, &blockRect);
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);
}

void Game::generateNextTetromino() {
    TetrominoType type = static_cast<TetrominoType>(rand() % 7);
    nextTetromino = std::make_unique<Tetromino>(type, 0, 0);
}

void Game::spawnTetromino() {
    currentTetromino = std::move(nextTetromino);
    currentTetromino->position.x = 3;
    currentTetromino->position.y = 0;

    generateNextTetromino();

    if (!isValidPosition(*currentTetromino, currentTetromino->position.x, currentTetromino->position.y)) {
        gameOver = true;
    }
}

bool Game::isValidPosition(const Tetromino& piece, int newX, int newY) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (piece.shape[i][j] != 0) {
                int boardX = newX + j;
                int boardY = newY + i;

                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT) {
                    return false;
                }
                if (boardY >= 0 && board[boardY][boardX] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Game::lockTetromino() {
    int blockType = static_cast<int>(currentTetromino->type) + 1;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentTetromino->shape[i][j] != 0) {
                int boardX = currentTetromino->position.x + j;
                int boardY = currentTetromino->position.y + i;
                if (boardY >= 0) {
                    board[boardY][boardX] = blockType;
                }
            }
        }
    }
    clearLines();
    updateBoardTexture();
    spawnTetromino();
}

void Game::clearLines() {
    for (int y = BOARD_HEIGHT - 1; y >= 0; --y) {
        bool lineIsFull = true;
        for (int x = 0; x < BOARD_WIDTH; ++x) {
            if (board[y][x] == 0) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            for (int row = y; row > 0; --row) {
                board[row] = board[row - 1];
            }
            board[0] = std::vector<int>(BOARD_WIDTH, 0);
            y++;
        }
    }
}

void Game::handleInput(const SDL_Event& event) {
    if(gameOver) return;
    
    if (event.type == SDL_KEYDOWN) {
        float currentX = currentTetromino->position.x;
        float currentY = currentTetromino->position.y;

        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                if (isValidPosition(*currentTetromino, currentX - 1, currentY)) {
                    currentTetromino->position.x--;
                }
                break;
            case SDLK_RIGHT:
                if (isValidPosition(*currentTetromino, currentX + 1, currentY)) {
                    currentTetromino->position.x++;
                }
                break;
            case SDLK_DOWN:
                if (isValidPosition(*currentTetromino, currentX, currentY + 1)) {
                    currentTetromino->position.y++;
                }
                break;
            case SDLK_UP:
                {
                    const auto originalShape = currentTetromino->shape;
                    currentTetromino->rotateShape();

                    bool moved = false;
                    std::vector<std::pair<int, int>> kicks = {{0, 0}, {-1, 0}, {1, 0}, {-2, 0}, {2, 0}, {0, -1}};
                    for(const auto& kick : kicks) {
                        if (isValidPosition(*currentTetromino, currentX + kick.first, currentY + kick.second)) {
                            currentTetromino->position.x += kick.first;
                            currentTetromino->position.y += kick.second;
                            moved = true;
                            break;
                        }
                    }

                    if (!moved) {
                        currentTetromino->shape = originalShape;
                    }
                }
                break;
        }
    }
}

void Game::update(float deltaTime) {
    if (gameOver) {
        return;
    }
    
    fallTimer += deltaTime;
    
    if (fallTimer >= fallSpeed) {
        if (isValidPosition(*currentTetromino, currentTetromino->position.x, currentTetromino->position.y + 1)) {
            currentTetromino->position.y++;
        } else {
            lockTetromino();
        }
        fallTimer = 0.0f;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 25, 25, 40, 255);
    SDL_RenderClear(renderer);

    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

    int boardPixelWidth = BOARD_WIDTH * BLOCK_SIZE;
    int boardPixelHeight = BOARD_HEIGHT * BLOCK_SIZE;
    
    int boardOffsetX = (windowWidth - boardPixelWidth) / 2;
    int boardOffsetY = (windowHeight - boardPixelHeight) / 2;

    SDL_Rect boardDestRect = { boardOffsetX, boardOffsetY, boardPixelWidth, boardPixelHeight };
    SDL_RenderCopy(renderer, boardTexture, NULL, &boardDestRect);

    if (currentTetromino) {
         for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (currentTetromino->shape[i][j] != 0) {
                    SDL_FRect blockRect = {
                        (float)(boardOffsetX + (currentTetromino->position.x + j) * BLOCK_SIZE),
                        (float)(boardOffsetY + (currentTetromino->position.y + i) * BLOCK_SIZE),
                        (float)BLOCK_SIZE,
                        (float)BLOCK_SIZE
                    };
                    SDL_RenderCopyF(renderer, currentTetromino->getTexture(), NULL, &blockRect);
                }
            }
        }
    }
    
    if (border) {
        border->render(renderer);
    }
    
    if (nextTetromino) {
        int nextBoxX = boardOffsetX + boardPixelWidth + 50;
        int nextBoxY = boardOffsetY;
        
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (nextTetromino->shape[i][j] != 0) {
                    SDL_FRect blockRect = {
                        (float)(nextBoxX + j * BLOCK_SIZE),
                        (float)(nextBoxY + i * BLOCK_SIZE),
                        (float)BLOCK_SIZE,
                        (float)BLOCK_SIZE
                    };
                    SDL_RenderCopyF(renderer, nextTetromino->getTexture(), NULL, &blockRect);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}

bool Game::isGameOver() {
    return gameOver;
}
