#include <iostream>
#include "Field.h"

#define DEFEAT -1
#define ONGOING 0
#define DRAW 1
#define VICTORY 2

Field::Field(int size) : size(size) {
    field = std::vector<std::vector<Node *>>();

    for (auto x = 0; x < size; ++x) {
        field.push_back(std::vector<Node *>());

        for (auto y = 0; y < size; ++y) {
            field[x].push_back(nullptr);
        }
    }
}

void Field::setPlay(int x, int y, bool firstPlayer) {
    field[x][y] = new Node(firstPlayer);
}

int Field::getTotalEmptyNodes() {
    setEmptyNodes();
    return totalEmptyNodes;
}

void Field::setEmptyNodes() {
    totalEmptyNodes = 0;

    for (auto x = 0; x < size; ++x) {
        for (auto y = 0; y < size; ++y) {
            if (field[x][y] == nullptr)
            {
                totalEmptyNodes++;
            }
        }
    }
}

std::vector<std::pair<int, int>> *Field::getEmptyNodes() {
    auto emptyNodes = new std::vector<std::pair<int, int>>();

    for (auto x = 0; x < size; ++x) {
        for (auto y = 0; y < size; ++y) {
            if (field[x][y] == nullptr) {
                emptyNodes->push_back(std::make_pair(x, y));
            }
        }
    }

    return emptyNodes;
}

int Field::getGameStatus() {
    setGameStatus();
    return gameStatus;
}

void Field::setGameStatus() {
    auto draw = true;

    for (auto i = 0; i < size; ++i) {
        auto circle = false;
        auto cross = false;
        for (auto j = 0; j < size; ++j) {

            // Nenhuma jogada no local
            if (field[i][j] == nullptr) {
                draw = false;
                break;
            }
            if (field[i][j]->isFirstPlayer()) {
                circle = true;
            }
            else {
                cross = true;
            }

            if (circle && cross) {
                break;
            }
        }

        if (circle && !cross) {
            gameStatus = VICTORY;
            return;
        }
        else if (cross && !circle) {
            gameStatus = DEFEAT;
            return;
        }
    }

    if (draw) {
        gameStatus = DRAW;
    }
    else {
        gameStatus = ONGOING;
    }

}

void Field::printField() {
    for (auto x = 0; x < size; ++x) {
        std::cout << "|";
        for (auto y = 0; y < size; ++y) {
            if (field[x][y] == nullptr) {
                std::cout << " _ |";
            }
            else if (field[x][y]->isFirstPlayer()) {
                std::cout << " O |";
            }
            else {
                std::cout << " X |";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Resultado: " << getGameStatus() << std::endl << std::endl;

}
