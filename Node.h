#ifndef GAME_THEORY_ALGORITHM_NODE_H
#define GAME_THEORY_ALGORITHM_NODE_H

class Node {
    bool firstPlayer;
    int value;
public:

    Node(bool firstPlayer);

    bool isFirstPlayer() const;

    int getValue() const;
    void setValue(int value);
};


#endif //GAME_THEORY_ALGORITHM_NODE_H
