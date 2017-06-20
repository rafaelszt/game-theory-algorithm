#include <iostream>
#include "SearchAlgorithm.h"

std::vector<Field *> *SearchAlgorithm::generatePossiblePlays(
        Field *f, bool firstPlayer) {
    auto possiblePlays = new std::vector<Field *>();
    auto emptyNodes = f->getEmptyNodes();

    for (auto it = emptyNodes->begin(); it != emptyNodes->end(); ++it) {
        auto field = new Field(*f);

        field->setPlay(it->first, it->second, firstPlayer);

        possiblePlays->push_back(field);
    }

    return possiblePlays;
}

statusCoordinate SearchAlgorithm::getHeuristicValue(Field *field) {
    auto win_rate = field->totalWinPossibilities();

    auto lastPlay = field->getPlayMade();
    return std::make_pair(win_rate,
                std::make_pair(lastPlay.second.first, lastPlay.second.second));
}

statusCoordinate SearchAlgorithm::minimumValue(statusCoordinate a, statusCoordinate b) {
    return a.first >= b.first ? b : a;
}

statusCoordinate SearchAlgorithm::maximumValue(statusCoordinate a, statusCoordinate b) {
    return a.first >= b.first ? a : b;
}
