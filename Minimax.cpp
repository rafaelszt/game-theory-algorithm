#include <cmath>
#include "Minimax.h"

statusCoordinate Minimax::execute(Field *field, int depth, bool maximizingPlayer, bool firstPlayer) {
    if (depth == 0 || field->getGameStatus() != 0) {
        return getHeuristicValue(field);
    }

    auto bestValue = std::make_pair(
            maximizingPlayer ? -999999999 : 999999999,
            std::make_pair(-1, -1));

    auto plays = generatePossiblePlays(field, firstPlayer);

    for (auto it = plays->begin(); it != plays->end(); ++it) {
        auto b = new Minimax();
        auto v = b->execute(*it, depth - 1, !maximizingPlayer, !firstPlayer);

        bestValue = maximizingPlayer ?
                    maximumValue(bestValue, v) :
                    minimumValue(bestValue, v);

        Field::incrementExpanded();
    }

    return bestValue;
}
