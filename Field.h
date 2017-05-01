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

    void setGameStatus();
    void setEmptyNodes();
public:

    Field(int size);
    void setPlay(int x, int y, bool firstPlayer);
    int getTotalEmptyNodes();
    int getGameStatus() const;
    std::vector<std::pair<int, int>> *getEmptyNodes();

};


#endif //GAME_THEORY_ALGORITHM_FIELD_H
