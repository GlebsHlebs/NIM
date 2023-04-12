#pragma once

#include "State.h"
#include "Move.h"
#include "StateSpaceGraphEdge.h"
#include <vector>
#include <random>
#include <utility> 
#include <cstdlib> 

class StateSpaceGraphEdge;

class StateSpaceGraphNode {
public:
    StateSpaceGraphNode(const State& state);
    StateSpaceGraphNode(const State& state, const Move& move);

    State getState() const;
    Move getMove() const;
    std::vector<StateSpaceGraphEdge*> getEdges() const;

    void addEdge(StateSpaceGraphEdge*);
    bool isLeaf() const;

    void setMinimaxValue(int);
    void setParentEdge(StateSpaceGraphEdge* edge);

    void applyMove(State& state, const Move& move);
    std::vector<Move> getLegalMoves(const State& state);

    int getHeuristicValue(State& current_state, bool is_maximizing_player);
    int getMinimaxValue(bool is_maximizing_player, State& current_state);
    Move getMoveFromParent() const;
    StateSpaceGraphEdge* getParentEdge() const;

private:
    State state;
    Move move;
    std::vector<StateSpaceGraphEdge*> edges;
    int minimax_value;
    StateSpaceGraphEdge* parent_edge_;
};