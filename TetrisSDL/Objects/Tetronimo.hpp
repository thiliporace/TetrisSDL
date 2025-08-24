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

    void rotateShape();

    std::array<std::array<int, 4>, 4> shape;
    std::array<std::array<int, 4>, 4> getShapeForType(TetrominoType type);
    TetrominoType type;
};
#endif /* Tetronimo_hpp */
