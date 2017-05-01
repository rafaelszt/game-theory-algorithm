#include "Node.h"


Node::Node(bool firstPlayer) : firstPlayer(firstPlayer) {}

bool Node::isFirstPlayer() const {
    return firstPlayer;
}

int Node::getValue() const {
    return value;
}

void Node::setValue(int value) {
    Node::value = value;
}
