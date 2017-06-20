#ifndef GAME_THEORY_ALGORITHM_FIELD_H
#define GAME_THEORY_ALGORITHM_FIELD_H

#include <vector>
#include "Node.h"

using nodeMatrix = std::vector<std::vector<Node *>>;
using play = std::pair<int, std::pair<int, int>>;

class Field {
private:
    int size;
    nodeMatrix field;
    int gameStatus;
    static int expanded;
    play playMade;

    void setGameStatus();

    std::vector<Node *> *getColumnResult(int y);
    std::vector<Node *> *getLeftDiagonalResult();
    std::vector<Node *> *getRightDiagonalResult();

    int getLineResult(std::vector<Node *> line);

    std::vector<std::vector<Node *>*> *getMatrixAsVector();
public:
    Field(int size);

    bool setPlay(int x, int y, bool firstPlayer);
    int getGameStatus();
    std::vector<std::pair<int, int>> *getEmptyNodes();

    void printField();

    static int incrementExpanded();
    play getPlayMade() const;

    void resetPlayMade();

    int totalWinPossibilities();

};


#endif //GAME_THEORY_ALGORITHM_FIELD_H
