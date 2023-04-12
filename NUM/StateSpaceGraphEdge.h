#pragma once

#include "State.h"
#include "StateSpaceGraphNode.h"

class StateSpaceGraphNode;

class StateSpaceGraphEdge {
public:
    StateSpaceGraphEdge(StateSpaceGraphNode* from_node, StateSpaceGraphNode* to_node, const Move& move);

    StateSpaceGraphNode* getFromNode() const;
    StateSpaceGraphNode* getToNode() const;
    Move getMove() const;

private:
    StateSpaceGraphNode* from_node;
    StateSpaceGraphNode* to_node;
    Move move;
};