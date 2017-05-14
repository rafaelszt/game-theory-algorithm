#ifndef GAME_THEORY_ALGORITHM_FIELD_H
#define GAME_THEORY_ALGORITHM_FIELD_H

#include <vector>
#include "Node.h"

using nodeMatrix = std::vector<std::vector<Node *>>;

class Field {
private:
    int size;
    nodeMatrix field;
    int totalEmptyNodes;
    int gameStatus;
    std::pair<bool, std::pair<int, int>> lastPlay;

    void setGameStatus();
    void setEmptyNodes();

    std::vector<Node *> *getColumnResult(int y);
    std::vector<Node *> *getLeftDiagonalResult();
    std::vector<Node *> *getRightDiagonalResult();

    int getLineResult(std::vector<Node *> line);
public:
    Field(int size);
    void setPlay(int x, int y, bool firstPlayer);
    int getTotalEmptyNodes();
    int getGameStatus();
    std::vector<std::pair<int, int>> *getEmptyNodes();

    void saveFieldToFile();
    void printField();

    int getSize() const;
    const std::pair<bool, std::pair<int, int>> &getLastPlay() const;

};


#endif //GAME_THEORY_ALGORITHM_FIELD_H
