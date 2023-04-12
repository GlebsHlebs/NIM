#pragma once
#include <vector>

enum class Player {
    MAX,
    MIN
};

class State {
public:
    State(const std::vector<int>& piles, int current_player);

    int getPileSize(int index) const;
    const std::vector<int>& getPiles() const;

    void removeObjects(int pile_index, int num_objects);

    Player getPlayer() const;

    bool operator==(const State& other) const;
    bool operator!=(const State& other) const;
    std::vector<int>::iterator begin() { return piles.begin(); }
    std::vector<int>::iterator end() { return piles.end(); }

private:
    std::vector<int> piles;
    Player player;
};