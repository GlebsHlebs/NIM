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

std::vector<Move> StateSpaceGraphNode::getLegalMoves(const State& state) {
    std::vector<Move> legal_moves;
    const auto& piles = state.getPiles();
    for (int i = 0; i < piles.size(); i++) {
        for (int j = 1; j <= piles[i]; j++) {
            legal_moves.emplace_back(i, j);
        }
    }
    return legal_moves;
}


void StateSpaceGraphNode::applyMove(State& state, const Move& move) {
    state.removeObjects(move.getPileIndex(), move.getNumObjects());
}

int StateSpaceGraphNode::getHeuristicValue(State& current_state, bool is_maximizing_player) {
    int remaining_stones = 0;
    for (int pile_size : current_state) {
        remaining_stones ^= pile_size;
    }
    if (remaining_stones == 0) {
        return is_maximizing_player ? -1 : +1;
    }

    // Monte Carlo simulation
    int num_simulations = 100;
    int num_wins = 0;
    std::mt19937 rng(std::random_device{}());
    for (int i = 0; i < num_simulations; i++) {
        State sim_state = current_state;
        bool sim_is_maximizing_player = is_maximizing_player;
        while (true) {
            std::vector<Move> legal_moves = getLegalMoves(sim_state);
            if (legal_moves.empty()) {
                break;  // game over
            }
            if (sim_is_maximizing_player) {
                // choose a random move
                Move random_move = legal_moves[rng() % legal_moves.size()];
                applyMove(sim_state, random_move);
            }
            else {
                // choose the move that leads to the smallest remaining stones
                int best_move_value = std::numeric_limits<int>::max();
                Move best_move;
                for (Move move : legal_moves) {
                    State next_state = sim_state;
                    applyMove(next_state, move);
                    int remaining_stones = 0;
                    for (int pile_size : next_state) {
                        remaining_stones ^= pile_size;
                    }
                    if (remaining_stones < best_move_value) {
                        best_move_value = remaining_stones;
                        best_move = move;
                    }
                }
                applyMove(sim_state, best_move);
            }
            sim_is_maximizing_player = !sim_is_maximizing_player;
        }
        // count the number of wins
        int sim_remaining_stones = 0;
        for (int pile_size : sim_state) {
            sim_remaining_stones ^= pile_size;
        }
        if ((sim_remaining_stones == 0 && sim_is_maximizing_player) || (sim_remaining_stones != 0 && !sim_is_maximizing_player)) {
            num_wins++;
        }
    }

    // estimate the probability of winning from the current state
    double win_probability = static_cast<double>(num_wins) / num_simulations;
    if (is_maximizing_player) {
        return static_cast<int>(100.0 * win_probability);
    }
    else {
        return static_cast<int>(-100.0 * win_probability);
    }
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