#include "Node.h"

Node::Node(bool firstPlayer) : firstPlayer(firstPlayer) {}

bool Node::isFirstPlayer() const {
    return firstPlayer;
}
