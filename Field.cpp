#include "Field.h"

Field::Field(int size) : size(size) {
    field = std::vector<std::vector<Node *>>();

    for (auto x = 0; x < size; ++x) {
        field[x] = std::vector<Node *>();

        for (auto y = 0; y < size; ++y) {
            field[x][y] = nullptr;
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
            if (field[x][y] != nullptr) {
                emptyNodes->push_back(std::make_pair(x, y));
            }
        }
    }

    return emptyNodes;
}

/*
 * -1 - DEFEAT
 * 0 - ONGOING
 * 1 - DRAW
 * 2 - VICTORY
 */
int Field::getGameStatus() const {
    return gameStatus;
}

void Field::setGameStatus() {

}
