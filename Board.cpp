#include <iostream>
#include "Board.h"

using namespace std;

Board::Board() {
    // Initialize the grid to be 10x10, empty spaces will have an '-'
    grid.assign(10, vector<char>(10, '-'));
}

const vector<vector<char>>& Board::getGrid() const {
    return grid;
}

void Board::addBugToBoard(const Bug& bug) {
    // Get bug position
    pair<int, int> position = bug.getPosition();

    // Check if the position is within bounds
    if (position.first >= 0 && position.first < grid.size() && position.second >= 0 && position.second < grid[0].size()) {
        char bugType = bug.getType();
        // Add bug to the bug board at the found position and put its type on the board
        grid[position.first][position.second] = bug.getType();
    } else {
        cerr << "Bug position is out of bounds!" << endl; // Error message if bug is out of bounds
    }
}