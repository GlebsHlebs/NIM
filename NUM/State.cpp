#include "State.h"

State::State(const std::vector<int>& piles, int current_player)
    : piles(piles), player(static_cast<Player>(current_player - 1))
{}


int State::getPileSize(int index) const {
    return piles[index];
}

const std::vector<int>& State::getPiles() const {
    return piles;
}

void State::removeObjects(int pile_index, int num_objects) {
    piles[pile_index] -= num_objects;
}

Player State::getPlayer() const {
    return player;
}

bool State::operator==(const State& other) const {
    return piles == other.piles;
}

bool State::operator!=(const State& other) const {
    return piles != other.piles;
}