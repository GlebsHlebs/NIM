#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "StateGraph.h"
#include "Move.h"
#include "State.h"

class NimGame {
public:
    NimGame(int, int, int);

    void play();

    State getState() const;

    int evaluateState() const;

private:
    std::vector<int> piles;
    int current_player;
    int moves_played;

    bool is_game_over();

    void display_board();

    void display_result();

    void player_move();

    void computer_move(StateGraph& graph);
};