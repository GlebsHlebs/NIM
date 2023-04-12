#include "StateSpaceGraphEdge.h"

StateSpaceGraphEdge::StateSpaceGraphEdge(StateSpaceGraphNode* from_node, StateSpaceGraphNode* to_node, const Move& move)
    : from_node(from_node), to_node(to_node), move(move) 
{
    to_node->setParentEdge(this);
}

StateSpaceGraphNode* StateSpaceGraphEdge::getFromNode() const {
    return from_node;
}

StateSpaceGraphNode* StateSpaceGraphEdge::getToNode() const {
    return to_node;
}

Move StateSpaceGraphEdge::getMove() const {
    return move;
}