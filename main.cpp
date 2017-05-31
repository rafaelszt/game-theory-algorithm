#include <iostream>
#include "Field.h"
#include "Minimax.h"
#include "AlphaBeta.h"

void makePlay(Field *f, bool firstPlayer) {
    std::cout << "X: ";
    auto x = 0;
    std::cin >> x;

    std::cout << "Y: ";
    auto y = 0;
    std::cin >> y;

    auto success = f->setPlay(x, y, firstPlayer);

    if (!success) {
        makePlay(f, firstPlayer);
    }
}

int main()
{
    auto field = new Field(3);

    field->printField();

    auto minimax = new AlphaBeta();

    auto depth = 9;
    auto maximizingPlayer = true;
    auto firstPlayer = true;

    while(field->getGameStatus() == 0) {
        if (firstPlayer) {
            makePlay(field, true);
        }
        else {
            auto play = *minimax->execute(field, depth, maximizingPlayer, firstPlayer);
            field->setPlay(play.second.first, play.second.second, firstPlayer);
        }

        field->printField();

        depth--;
        maximizingPlayer = !maximizingPlayer;
        firstPlayer = !firstPlayer;
    }


    return 0;
}
