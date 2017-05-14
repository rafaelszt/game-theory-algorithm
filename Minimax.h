#ifndef GAME_THEORY_ALGORITHM_MINIMAX_H
#define GAME_THEORY_ALGORITHM_MINIMAX_H

#include "Field.h"
#include <cmath>

using statusCoordinate = std::pair<int, std::pair<int, int>>*;

class Minimax {
private:
    std::vector<Field *> *generatePossiblePlays(Field *f, bool firstPlayer);

    statusCoordinate minimumValue(statusCoordinate a, statusCoordinate b);
    statusCoordinate maximumValue(statusCoordinate a, statusCoordinate b);

    int getBoardPoint(int x, int y);

public:
    statusCoordinate execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer);

};


#endif //GAME_THEORY_ALGORITHM_MINIMAX_H
