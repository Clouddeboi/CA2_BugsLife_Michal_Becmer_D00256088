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

void Board::displayBoard()
{

    for(int i = 0; i < 10; ++i)//loops rows
    {
        for(int j = 0; j < 10; ++j)//loops columns
        {
            cout << grid[i][j] << "  ";//output the location of the character followed by an empty space
        }
        cout << endl;//makes rows by moving to next line after a row
    }
}

bool Board::isWayBlocked(const pair<int, int>& pos, Direction dir) const {
    //extracting x and y coordinates from pair
    int x = pos.first;
    int y = pos.second;

    //Check the direction of movement and whether the way is blocked
    switch (dir) {
        //Check if moving north would lead to a position out of bounds
        //or if the position immediately north of the bug is occupied
        case Direction::North:
            return (y + 1 >= grid.size()) || (grid[y + 1][x] != '-');
        case Direction::East:
            return (x + 1 >= grid[0].size()) || (grid[y][x + 1] != '-');
        case Direction::South:
            return (y - 1 < 0) || (grid[y - 1][x] != '-');
        case Direction::West:
            return (x - 1 < 0) || (grid[y][x - 1] != '-');
        default:
            return true; // Unknown direction
    }
}
