#pragma once
#include "StateSpaceGraphNode.h"
#include <vector>
#include <queue>

class StateGraph {
public:
    StateGraph(const std::vector<int>& piles, int Current_player);
    ~StateGraph();
    State getRootState() const;
    StateSpaceGraphNode* getNode(const State& state) const;

private:
    StateSpaceGraphNode* root_node;

    void generateStateSpaceGraph(StateSpaceGraphNode* parent_node);
    std::vector<Move> generateMoves(const State& state);
    State applyMove(const State& state, const Move& move);
    void deleteSubtree(StateSpaceGraphNode* node);
};