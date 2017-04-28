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
