#ifndef GAME_THEORY_ALGORITHM_NODE_H
#define GAME_THEORY_ALGORITHM_NODE_H

class Node {
    bool firstPlayer;
public:

    Node(bool firstPlayer);

    bool isFirstPlayer() const;
};


#endif //GAME_THEORY_ALGORITHM_NODE_H
