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
    playMade = std::make_pair(-1, std::make_pair(-1, -1));

    for (auto x = 0; x < size; ++x) {
        field.push_back(std::vector<Node *>());

        for (auto y = 0; y < size; ++y) {
            field[x].push_back(nullptr);
        }
    }
}

bool Field::setPlay(int x, int y, bool firstPlayer) {
    // Verifica se já não tem um pair salvo
    if (!firstPlayer && playMade.first == -1) {
        playMade = std::make_pair(firstPlayer, std::make_pair(x, y));
    }

    if (field[x][y] == nullptr) {
        field[x][y] = new Node(firstPlayer);

        return true;
    }

    return false;
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

std::vector<std::vector<Node *>*> *Field::getMatrixAsVector() {
    auto lineResults = new std::vector<std::vector<Node *>*>();

    lineResults->push_back(getLeftDiagonalResult());
    lineResults->push_back(getRightDiagonalResult());

    for (auto y = 0; y < size; ++y) {
        // Coloca a linha no resultado
        lineResults->push_back(&field[y]);
        lineResults->push_back(getColumnResult(y));
    }

    return lineResults;
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

    auto lineResults = getMatrixAsVector();

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
            DEFEAT : VICTORY;
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

    std::cout << "Expandidos: " << expanded << std::endl << std::endl;
    expanded = 0;

}

play Field::getPlayMade() const {
    return playMade;
}

int Field::incrementExpanded() {
    return ++expanded;
}

void Field::resetPlayMade() {
    playMade = std::make_pair(-1, std::make_pair(-1, -1));
}

int Field::totalWinPossibilities() {
    auto total = std::make_pair(0, 0);

    // Linha
    for (auto x = 0; x < size; ++x) {
        auto empty_line = true;
        auto cross_only = true;
        auto circle_only = true;

        for (auto y = 0; y < size; ++y) {
            if (field[x][y] == nullptr) {
                continue;
            }
            else if (field[x][y]->isFirstPlayer()) {
                cross_only = false;
            }
            else {
                circle_only = false;
            }
            empty_line = false;
        }

        if (empty_line) {
            total.first++;
            total.second++;
        }
        else if (circle_only) {
            total.first++;
        }
        else if (cross_only) {
            total.second++;
        }
    }

    // Coluna
    for (auto x = 0; x < size; ++x) {
        auto empty_line = true;
        auto cross_only = true;
        auto circle_only = true;

        for (auto y = 0; y < size; ++y) {
            if (field[y][x] == nullptr) {
                continue;
            }
            else if (field[y][x]->isFirstPlayer()) {
                cross_only = false;
            }
            else {
                circle_only = false;
            }

            empty_line = false;
        }

        if (empty_line) {
            total.first++;
            total.second++;
        }
        else if (circle_only) {
            total.first++;
        }
        else if (cross_only) {
            total.second++;
        }
    }

    // Diagonal direita-esquerda
    auto empty_line = true;
    auto cross_only = true;
    auto circle_only = true;

    auto x = size-1;
    auto y = 0;
    for (; y < size && x >= 0; --x, y++) {

        if (field[y][x] == nullptr) {
            continue;
        } else if (field[y][x]->isFirstPlayer()) {
            cross_only = false;
        } else {
            circle_only = false;
        }

        empty_line = false;
    }

    if (empty_line) {
        total.first++;
        total.second++;
    }
    else if (circle_only) {
        total.first++;
    }
    else if (cross_only) {
        total.second++;
    }

    // Diagonal Principal
    empty_line = true;
    cross_only = true;
    circle_only = true;

    for (auto y = 0; y < size; ++y) {
        if (field[y][y] == nullptr) {
            continue;
        }
        else if (field[y][y]->isFirstPlayer()) {
            cross_only = false;
        }
        else {
            circle_only = false;
        }

        empty_line = false;
    }

    if (empty_line) {
        total.first++;
        total.second++;
    }
    else if (circle_only) {
        total.first++;
    }
    else if (cross_only) {
        total.second++;
    }

    return total.first - total.second;
}
