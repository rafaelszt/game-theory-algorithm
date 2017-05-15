#ifndef GAME_THEORY_ALGORITHM_ALPHABETA_H
#define GAME_THEORY_ALGORITHM_ALPHABETA_H


#include "SearchAlgorithm.h"

class AlphaBeta : public SearchAlgorithm {
private:
    int maximumValue(int a, int b);
    int minimumValue(int a, int b);

    statusCoordinate execute(Field *field, int depth, int alpha, int beta, bool maximizingPlayer, bool firstPlayer);

public:
    statusCoordinate execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer);

};


#endif //GAME_THEORY_ALGORITHM_ALPHABETA_H
