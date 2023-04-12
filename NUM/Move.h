#pragma once

class Move {
public:
    Move() : pile_index(-1), num_objects(-1) {}
    Move(int ppile_index, int num_objects) : pile_index(ppile_index), num_objects(num_objects) {}

    int getPileIndex() const;
    int getNumObjects() const;
private:
    int pile_index;
    int num_objects;
};