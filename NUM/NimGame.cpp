#include "NimGame.h"

NimGame::NimGame(int num_piles, int num_objects, int player_num) :
    piles(num_piles, num_objects), current_player(player_num - 1), moves_played(0) {}

void NimGame::play() {
    StateGraph graph(piles, current_player);

    while (!is_game_over()) {
        display_board();
        if (current_player == 0) {
            player_move();
        }
        else {
            computer_move(graph);
        }
        current_player = (current_player + 1) % 2;
    }

    display_result();
}

State NimGame::getState() const {
    return State(piles, current_player);
}

int NimGame::evaluateState() const {
    // Check whose move it is
    bool is_maximizing_player = (moves_played % 2 == 0);

    // Set the heuristic value based on whose move it is
    if (is_maximizing_player) {
        return 1;
    }
    else {
        return -1;
    }
}

bool NimGame::is_game_over() {
    return std::all_of(piles.begin(), piles.end(), [](int i) { return i == 0; });
}

void NimGame::display_board() {
    std::cout << "---------------------" << std::endl;
    for (int i = 0; i < piles.size(); i++) {
        std::cout << "Pile " << i + 1 << ": ";
        for (int j = 0; j < piles[i]; j++) {
            std::cout << "* ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

void NimGame::display_result() {
    if (current_player == 0) {
        std::cout << "Congratulations! You win!" << std::endl;
    }
    else {
        std::cout << "Sorry, you lost. Better luck next time!" << std::endl;
    }
}

void NimGame::player_move() {
    int pile_num, objects_to_remove;
    bool valid_move = false;

    while (!valid_move) {
        std::cout << "Your turn!" << std::endl;
        std::cout << "Enter the pile number and number of objects to remove: ";
        std::cin >> pile_num >> objects_to_remove;

        pile_num--;

        if (pile_num < 0 || pile_num >= piles.size()) {
            std::cout << "Invalid pile number. Please try again." << std::endl;
        }
        else if (piles[pile_num] < objects_to_remove) {
            std::cout << "Invalid number of objects to remove. Please try again." << std::endl;
        }
        else {
            piles[pile_num] -= objects_to_remove;
            moves_played;
            valid_move = true;

        }
    }
}
void NimGame::computer_move(StateGraph& graph) {
    // Get the state space graph node for the current state
    State current_state = getState();
    StateSpaceGraphNode* current_node = graph.getNode(current_state);

    // Find the child node with the highest minimax value
    StateSpaceGraphNode* best_child = nullptr;
    int best_value = std::numeric_limits<int>::min();
    bool is_maximizing_player = (current_state.getPlayer() == Player::MAX);
    for (StateSpaceGraphEdge* edge : current_node->getEdges()) {
        StateSpaceGraphNode* child = edge->getToNode();
        int value = child->getMinimaxValue(is_maximizing_player, current_state);
        if (value > best_value) {
            best_child = child;
            best_value = value;
        }
    }

    // Make the move that leads to the best child node
    if (best_child != nullptr) {
        Move move = best_child->getMoveFromParent();
        std::cout << "index " << move.getPileIndex() << " number" << move.getNumObjects() << std::endl;
        piles[move.getPileIndex()] -= move.getNumObjects();
        std::cout << "Computer removes " << move.getNumObjects() << " objects from pile " << move.getPileIndex() + 1 << "." << std::endl;
    }
    else {
        std::cout << "Error: No valid move found." << std::endl;
    }
}

