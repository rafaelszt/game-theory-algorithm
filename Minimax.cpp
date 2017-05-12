#include "Minimax.h"

std::vector<Field *> *Minimax::generatePossiblePlays(Field *f, bool firstPlayer) {
    auto possiblePlays = new std::vector<Field *>();
    auto emptyNodes = f->getEmptyNodes();

    for (auto it = emptyNodes->begin(); it != emptyNodes->end(); ++it) {
        auto field = new Field(*f);

        field->setPlay(it->first, it->second, firstPlayer);

        possiblePlays->push_back(field);
    }

    return possiblePlays;
}

int Minimax::execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer) {
    if (depth == 0 or field->getGameStatus() != 0) {
        field->printField();
        return field->getGameStatus();
    }

    auto bestValue = maximizingPlayer ? -INFINITY : INFINITY;
    auto plays = generatePossiblePlays(field, firstPlayer);

    for (auto it = plays->begin(); it != plays->end(); ++it) {
        auto b = new Minimax();
        auto v = b->execute(*it, depth - 1, !maximizingPlayer, !firstPlayer);
        bestValue = maximizingPlayer ?
                    maximumValue(bestValue, v) :
                    minimumValue(bestValue, v);
    }

    return bestValue;
}

int Minimax::minimumValue(int a, int b) {
    return a > b ? a : b;
}

int Minimax::maximumValue(int a, int b) {
    return b > a ? b : a;
}
