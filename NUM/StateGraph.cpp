#include "StateGraph.h"

StateGraph::StateGraph(const std::vector<int>& piles, int current_player) {
    // Create the root node with the initial state of the game
    root_node = new StateSpaceGraphNode(State(piles, current_player));

    // Generate the state space graph using a depth-first search
    generateStateSpaceGraph(root_node);
}

StateGraph::~StateGraph() {
    // Free memory by deleting all nodes in the state space graph
    deleteSubtree(root_node);
}

State StateGraph::getRootState() const {
    return root_node->getState();
}

StateSpaceGraphNode* StateGraph::getNode(const State& state) const {
    // Use a breadth-first search to find the node with the given state
    std::queue<StateSpaceGraphNode*> node_queue;
    node_queue.push(root_node);

    while (!node_queue.empty()) {
        StateSpaceGraphNode* current_node = node_queue.front();
        node_queue.pop();

        if (current_node->getState() == state) {
            return current_node;
        }

        for (StateSpaceGraphEdge* edge : current_node->getEdges()) {
            StateSpaceGraphNode* child_node = edge->getToNode();
            node_queue.push(child_node);
        }
    }

    // If the node with the given state is not found, return a null pointer
    return nullptr;
}

void StateGraph::generateStateSpaceGraph(StateSpaceGraphNode* parent_node) {
    State parent_state = parent_node->getState();

    // Generate all possible moves from the current state
    std::vector<Move> possible_moves = generateMoves(parent_state);

    // Create a child node for each possible move
    for (Move move : possible_moves) {
        // Apply the move to the parent state to get the child state
        State child_state = applyMove(parent_state, move);

        // Create a new node for the child state and add it as a child of the parent node
        StateSpaceGraphNode* child_node = new StateSpaceGraphNode(child_state, move);
        parent_node->addEdge(new StateSpaceGraphEdge(parent_node, child_node, move));
        // Recursively generate the state space graph for the child node
        generateStateSpaceGraph(child_node);
    }
}

std::vector<Move> StateGraph::generateMoves(const State& state) {
    std::vector<Move> moves;

    // Generate all possible moves for the current state
    for (int i = 0; i < state.getPiles().size(); i++) {
        for (int j = 1; j <= state.getPiles()[i]; j++) {
            moves.push_back(Move(i, j));
        }
    }

    return moves;
}

State StateGraph::applyMove(const State& state, const Move& move) {
    // Create a copy of the state and apply the move to it
    State new_state = state;
    new_state.removeObjects(move.getPileIndex(), move.getNumObjects());

    return new_state;
}

void StateGraph::deleteSubtree(StateSpaceGraphNode* node) {
    // Recursively delete all nodes in the subtree rooted at the given node
    for (StateSpaceGraphEdge* edge : node->getEdges()) {
        StateSpaceGraphNode* child_node = edge->getToNode();
        deleteSubtree(child_node);
    }
    delete node;
}