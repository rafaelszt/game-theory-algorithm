#ifndef GAME_THEORY_ALGORITHM_SEARCHALGORITHM_H
#define GAME_THEORY_ALGORITHM_SEARCHALGORITHM_H

#include "Field.h"
#include <cmath>

using statusCoordinate = std::pair<int, std::pair<int, int>>;

class SearchAlgorithm {
protected:
    std::vector<Field *> *generatePossiblePlays(Field *f, bool firstPlayer);

    statusCoordinate minimumValue(statusCoordinate a, statusCoordinate b);
    statusCoordinate maximumValue(statusCoordinate a, statusCoordinate b);
    statusCoordinate getHeuristicValue(Field *field);

public:
    virtual statusCoordinate execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer) = 0;
};


#endif //GAME_THEORY_ALGORITHM_SEARCHALGORITHM_H
