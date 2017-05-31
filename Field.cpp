#include <iostream>
#include <fstream>
#include "Field.h"

#define UNDEFINED -2
#define DEFEAT -1
#define ONGOING 0
#define DRAW 1
#define VICTORY 2

#define CROSS 1
#define CIRCLE 0
#define UNSET -1

int Field::expanded = 0;

Field::Field(int size) : size(size) {
    field = std::vector<std::vector<Node *>>();

    for (auto x = 0; x < size; ++x) {
        field.push_back(std::vector<Node *>());

        for (auto y = 0; y < size; ++y) {
            field[x].push_back(nullptr);
        }
    }
}

bool Field::setPlay(int x, int y, bool firstPlayer) {
    lastPlay = std::make_pair(firstPlayer, std::make_pair(x, y));

    if (field[x][y] == nullptr) {
        field[x][y] = new Node(firstPlayer);
        return true;
    }

    return false;
}

int Field::getTotalEmptyNodes() {
    setEmptyNodes();
    return totalEmptyNodes;
}

void Field::setEmptyNodes() {
    totalEmptyNodes = 9;

    for (auto x = 0; x < size; ++x) {
        for (auto y = 0; y < size; ++y) {
            if (field[x][y] == nullptr) {
                totalEmptyNodes--;
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


std::vector<Node *> *Field::getColumnResult(int y) {
    auto result = new std::vector<Node *>();

    for (auto x = 0; x < size; ++x) {
        result->push_back(field[x][y]);
    }

    return result;
}

std::vector<Node *> *Field::getLeftDiagonalResult() {
    auto result = new std::vector<Node *>();
    auto y = 0;

    for (auto x = y; x < size; ++x, ++y) {
        result->push_back(field[x][y]);
    }

    return result;
}

std::vector<Node *> *Field::getRightDiagonalResult() {
    auto result = new std::vector<Node *>();

    for (auto x = 0; x < size; ++x) {
        result->push_back(field[x][size - 1 - x]);
    }

    return result;
}

void Field::setGameStatus() {
    gameStatus = DRAW;

    auto lineResults = new std::vector<std::vector<Node *>*>();

    lineResults->push_back(getLeftDiagonalResult());
    lineResults->push_back(getRightDiagonalResult());

    for (auto y = 0; y < size; ++y) {
        // Coloca a linha no resultado
        lineResults->push_back(&field[y]);

        lineResults->push_back(getColumnResult(y));
    }

    for (auto itResult = lineResults->begin(); itResult != lineResults->end(); ++itResult) {
        auto result = getLineResult(**itResult);

        if (result == VICTORY || result == DEFEAT) {
            gameStatus = result;

            return;
        }
        else if (result == ONGOING) {
            gameStatus = result;
        }
    }

}

int Field::getLineResult(std::vector<Node *> line) {
    int previousPlay = UNSET;
    int result = UNDEFINED;

    for (auto play = line.cbegin(); play != line.cend(); ++play) {
            // Se encontrar um vazio continua o jogo
        if (*play == nullptr) {
            result = ONGOING;
            break;
        }
        else if (previousPlay == UNSET) {
            previousPlay = (*play)->isFirstPlayer() ?
                           CIRCLE : CROSS;
        }
        else {
            auto curPlay = (*play)->isFirstPlayer() ?
                           CIRCLE : CROSS;
            if (previousPlay != curPlay) {
                result = DRAW;
            }
        }
    }

    if (result == DRAW || result == ONGOING) {
        return result;
    }

    //Verifica qual jogada estava sendo feita
    return previousPlay == CIRCLE ?
            VICTORY : DEFEAT;
}

int Field::getSize() const {
    return size;
}

void Field::saveFieldToFile() {
    std::ofstream file;
    file.open("output.txt", std::ofstream::out | std::ofstream::app);

    for (auto x = 0; x < size; ++x) {
        file << "|";
        for (auto y = 0; y < size; ++y) {
            if (field[x][y] == nullptr) {
                file << " _ |";
            }
            else if (field[x][y]->isFirstPlayer()) {
                file << " O |";
            }
            else {
                file << " X |";
            }
        }
        file << std::endl;
    }
    file << "Resultado: " << getGameStatus() << std::endl << std::endl;

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
    std::cout << "Resultado: " << getGameStatus() << std::endl;
    std::cout << "Expandidos: " << expanded << std::endl << std::endl;
    expanded = 0;

}

const std::pair<bool, std::pair<int, int>> &Field::getLastPlay() const {
    return lastPlay;
}

int Field::incrementExpanded() {
    return ++expanded;
}
