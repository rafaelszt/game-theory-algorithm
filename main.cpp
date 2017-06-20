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

    auto rp = std::make_pair(-1, std::make_pair(-1, -1));
    auto success = f->setPlay(x, y, firstPlayer);

    if (!success) {
        makePlay(f, firstPlayer);
    }
}

int main()
{
    auto mx = 'y';
    std::cout << "Minimax? (y/n) ";
    std::cin >> mx;

    SearchAlgorithm *search_algorithm = new AlphaBeta();

    if (mx == 'y') {
        search_algorithm = new Minimax();
    }

    std::cin.clear();

    auto field = new Field(3);

    field->printField();

    auto depth = 9;
    auto maximizingPlayer = true;
    auto firstPlayer = true;

    while(field->getGameStatus() == 0) {
        if (firstPlayer) {
            makePlay(field, true);
        }
        else {
            auto play = search_algorithm->execute(
                    field, depth, maximizingPlayer, firstPlayer);

            // Efetua a jogada do computador
            field->setPlay(play.second.first, play.second.second, firstPlayer);

            field->resetPlayMade();
        }

        field->printField();

        depth--;
        maximizingPlayer = !maximizingPlayer;
        firstPlayer = !firstPlayer;
    }


    return 0;
}
