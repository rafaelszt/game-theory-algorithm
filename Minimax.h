#ifndef GAME_THEORY_ALGORITHM_MINIMAX_H
#define GAME_THEORY_ALGORITHM_MINIMAX_H

#include "SearchAlgorithm.h"
#include "Field.h"

using statusCoordinate = std::pair<int, std::pair<int, int>>;

class Minimax: public SearchAlgorithm {
public:
    statusCoordinate execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer);

};


#endif //GAME_THEORY_ALGORITHM_MINIMAX_H
