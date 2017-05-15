#include "AlphaBeta.h"

statusCoordinate AlphaBeta::execute(Field *field, int depth, int alpha, int beta, bool maximizingPlayer, bool firstPlayer) {
    if (depth == 0 or field->getGameStatus() != 0) {
        return getHeuristicValue(field);
    }

    auto bestValue = new std::pair<int, std::pair<int, int>>(
            maximizingPlayer ? -INFINITY : INFINITY,
            std::make_pair(-1, -1));

    auto plays = generatePossiblePlays(field, firstPlayer);

    for (auto it = plays->begin(); it != plays->end(); ++it) {
        auto b = new AlphaBeta();
        auto v = b->execute(*it, depth - 1, alpha, beta, !maximizingPlayer, !firstPlayer);

        bestValue = maximizingPlayer ?
                    SearchAlgorithm::maximumValue(bestValue, v) :
                    SearchAlgorithm::minimumValue(bestValue, v);

        alpha = maximizingPlayer ?
                maximumValue(alpha, bestValue->first) :
                minimumValue(beta, bestValue->first);

        if (alpha > beta) {
            break;
        }
    }

    return bestValue;
}

int AlphaBeta::maximumValue(int a, int b) {
    return a > b ?
            a : b;
}

int AlphaBeta::minimumValue(int a, int b) {
    return a > b ?
           b : a;
}

statusCoordinate AlphaBeta::execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer) {
    return execute(field, depth, -INFINITY, INFINITY, maximizingPlayer, firstPlayer);
}
