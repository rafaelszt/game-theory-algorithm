#include "SearchAlgorithm.h"

std::vector<Field *> *SearchAlgorithm::generatePossiblePlays(Field *f, bool firstPlayer) {
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
    auto lastPlay = field->getLastPlay();
    return new std::pair<int, std::pair<int, int>>(
                field->getGameStatus() + getBoardPoint(
                        lastPlay.second.first, lastPlay.second.first
                ),
                std::make_pair(lastPlay.second.first, lastPlay.second.second));
}

statusCoordinate SearchAlgorithm::minimumValue(statusCoordinate a, statusCoordinate b) {
    return a->first > b->first ? a : b;
}

statusCoordinate SearchAlgorithm::maximumValue(statusCoordinate a, statusCoordinate b) {
    return b->first > a->first ? b : a;
}

int SearchAlgorithm::getBoardPoint(int x, int y) {
    if ((x == 2 || x == 0) && (y == 2 || y == 0)) {
        return 6;
    }
    else if (x == 1 && y == 1) {
        return 8;
    }

    return 4;
}
