#include <iostream>
#include "NimGame.h"

int main() {
    int num_piles, num_objects, starting_player;

    // Prompt the user to enter the number of piles
    std::cout << "Enter the number of piles: ";
    std::cin >> num_piles;

    // Prompt the user to enter the number of objects in each pile
    std::cout << "Enter the number of objects in each pile: ";
    std::cin >> num_objects;

    // Prompt the user to choose the starting player
    std::cout << "Choose the starting player (0 for minimizer, 1 for maximizer): ";
    std::cin >> starting_player;

    // Create a new NimGame object with the specified number of piles and objects, and the chosen starting player
    NimGame game(num_piles, num_objects, starting_player);

    // Play the game
    game.play();

    return 0;
}