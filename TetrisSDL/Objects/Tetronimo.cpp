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
    : GameObject(startX, startY, 30, 30, getAssetPathForType(type)), type(type) {
    
    this->position.x = startX;
    this->position.y = startY;

    switch (type) {
        case TetrominoType::I:
            shape = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
        case TetrominoType::O:
            shape = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
        case TetrominoType::T:
            shape = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
        case TetrominoType::L:
            shape = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
        case TetrominoType::J:
            shape = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
        case TetrominoType::S:
            shape = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
        case TetrominoType::Z:
            shape = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
            break;
    }
}

void Tetromino::update(float deltaTime) {
    
}

void Tetromino::rotateShape() {
    std::vector<std::vector<int>> tempShape = shape;
    int n = shape.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            shape[i][j] = tempShape[n - 1 - j][i];
        }
    }
}
