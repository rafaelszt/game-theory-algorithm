#include <iostream>
#include "Minimax.h"
#include "Field.h"

int main()
{
    auto field = new Field(3);

    field->printField();

    auto minimax = new Minimax();

    auto depth = 9;
    auto maximizingPlayer = true;
    auto firstPlayer = true;

    while(field->getGameStatus() == 0) {
        auto play = *minimax->execute(field, depth, maximizingPlayer, firstPlayer);
        field->setPlay(play.second.first, play.second.second, firstPlayer);

        field->printField();

        depth--;
        maximizingPlayer = !maximizingPlayer;
        firstPlayer = !firstPlayer;
    }


    return 0;
}
