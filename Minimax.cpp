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

statusCoordinate Minimax::execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer) {
    if (depth == 0 or field->getGameStatus() != 0) {
        auto lastPlay = field->getLastPlay();
        return new std::pair<int, std::pair<int, int>>(
                field->getGameStatus(),
                std::make_pair(lastPlay.second.first, lastPlay.second.second));
    }

    auto bestValue = new std::pair<int, std::pair<int, int>>(
            maximizingPlayer ? -INFINITY : INFINITY,
            std::make_pair(-1, -1));

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

statusCoordinate Minimax::minimumValue(statusCoordinate a, statusCoordinate b) {
    return a->first > b->first ? a : b;
}

statusCoordinate Minimax::maximumValue(statusCoordinate a, statusCoordinate b) {
    return b->first > a->first ? b : a;
}
