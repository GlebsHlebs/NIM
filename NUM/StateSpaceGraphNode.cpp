#include "StateSpaceGraphNode.h"

StateSpaceGraphNode::StateSpaceGraphNode(const State& state) : state(state), minimax_value(0), parent_edge_(nullptr) {}
StateSpaceGraphNode::StateSpaceGraphNode(const State& state, const Move& move)
    : state(state), move(move), parent_edge_(nullptr)
{
    edges = std::vector<StateSpaceGraphEdge*>();
}

State StateSpaceGraphNode::getState() const { return state; }

Move StateSpaceGraphNode::getMove() const { return move; }

std::vector<StateSpaceGraphEdge*> StateSpaceGraphNode::getEdges() const { return edges; }

void StateSpaceGraphNode::addEdge(StateSpaceGraphEdge* edge) {
    edges.push_back(edge);
}

void StateSpaceGraphNode::setMinimaxValue(int value) {
    minimax_value = value;
}

bool StateSpaceGraphNode::isLeaf() const {
    return edges.empty();
}

int StateSpaceGraphNode::getHeuristicValue(State& current_state, bool is_maximizing_player) {
    int remaining_stones = 0;
    for (int pile_size : current_state) {
        remaining_stones ^= pile_size;
    }
    if (remaining_stones == 0) {
        return is_maximizing_player ? -1 : +1;
    }
    return 0;
}

void StateSpaceGraphNode::setParentEdge(StateSpaceGraphEdge* edge) {
    parent_edge_ = edge;
}

int StateSpaceGraphNode::getMinimaxValue(bool is_maximizing_player, State& current_state) {
    if (isLeaf()) {
        return getHeuristicValue(current_state, is_maximizing_player);
    }
    if (is_maximizing_player) {
        int best_value = std::numeric_limits<int>::min();
        for (StateSpaceGraphEdge* edge : edges) {
            StateSpaceGraphNode* child = edge->getToNode();
            int value = child->getMinimaxValue(false, current_state);
            if (value > best_value) {
                best_value = value;
            }
        }
        return best_value;
    }
    else {
        int best_value = std::numeric_limits<int>::max();
        for (StateSpaceGraphEdge* edge : edges) {
            StateSpaceGraphNode* child = edge->getToNode();
            int value = child->getMinimaxValue(true, current_state);
            if (value < best_value) {
                best_value = value;
            }
        }
        return best_value;
    }
}


Move StateSpaceGraphNode::getMoveFromParent() const {
    StateSpaceGraphEdge* parent_edge = getParentEdge();
    if (parent_edge == nullptr) {
        // This node is the root node and has no parent edge
        return Move();
    }
    else {
        return parent_edge->getMove();
    }
}

StateSpaceGraphEdge* StateSpaceGraphNode::getParentEdge() const {
    return parent_edge_;
}