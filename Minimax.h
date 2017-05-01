#ifndef GAME_THEORY_ALGORITHM_MINIMAX_H
#define GAME_THEORY_ALGORITHM_MINIMAX_H

#include "Field.h"
#include <cmath>

class Minimax {
private:
    std::vector<Field *> *generatePossiblePlays(Field *f, bool firstPlayer);
    int minimumValue(int a, int b);
    int maximumValue(int a, int b);

public:
    int execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer);

};


#endif //GAME_THEORY_ALGORITHM_MINIMAX_H
