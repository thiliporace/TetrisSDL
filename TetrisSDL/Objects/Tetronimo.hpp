//
//  Tetronimo.hpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#ifndef Tetronimo_hpp
#define Tetronimo_hpp

#include <stdio.h>

#include <vector>
#include <SDL2/SDL.h>

#include "GameObject.hpp"

enum class TetrominoType {
    I, O, T, L, J, S, Z
};

class Tetromino : public GameObject {
public:
    Tetromino(TetrominoType type, int startX, int startY);

    void update(float deltaTime) override;
    void rotateShape();

    std::vector<std::vector<int>> shape;
    TetrominoType type;
};
#endif /* Tetronimo_hpp */
