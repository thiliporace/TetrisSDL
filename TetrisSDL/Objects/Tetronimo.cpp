//
//  Tetronimo.cpp
//  TetrisSDL
//
//  Created by Thiago Liporace on 10/08/25.
//

#include "Tetronimo.hpp"
#include <map>
#include <string>

std::string getAssetPathForType(TetrominoType type) {
    static const std::map<TetrominoType, std::string> typeToPath = {
        {TetrominoType::I, "Tetromino_block1_1.png"},
        {TetrominoType::O, "Tetromino_block1_2.png"},
        {TetrominoType::T, "Tetromino_block1_3.png"},
        {TetrominoType::L, "Tetromino_block1_4.png"},
        {TetrominoType::J, "Tetromino_block1_5.png"},
        {TetrominoType::S, "Tetromino_block1_6.png"},
        {TetrominoType::Z, "Tetromino_block1_7.png"}
    };
    auto it = typeToPath.find(type);
    if (it != typeToPath.end()) {
        return it->second;
    }
    return "";
}

Tetromino::Tetromino(TetrominoType type, int startX, int startY)
    : GameObject(startX, startY, 30, 30, getAssetPathForType(type)), type(type), shape(getShapeForType(type)) {
    
    this->position.x = startX;
    this->position.y = startY;
}

std::array<std::array<int, 4>, 4> Tetromino::getShapeForType(TetrominoType type) {
    switch (type) {
        case TetrominoType::I:
            return {{
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
        case TetrominoType::O:
            return {{
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
        case TetrominoType::T:
            return {{
                {0, 1, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
        case TetrominoType::L:
            return {{
                {0, 0, 1, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
        case TetrominoType::J:
            return {{
                {1, 0, 0, 0},
                {1, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
        case TetrominoType::S:
            return {{
                {0, 1, 1, 0},
                {1, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
        case TetrominoType::Z:
            return {{
                {1, 1, 0, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }};
    }
    return {};
}

void Tetromino::rotateShape() {
    auto tempShape = shape;
    const int n = shape.size();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            shape[i][j] = tempShape[n - 1 - j][i];
        }
    }
}
