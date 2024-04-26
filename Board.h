#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include <vector>

using namespace std;

class Board {
protected:
    vector<vector<char>> grid; // Grid for the bug board

public:
    // Constructor
    Board();

    const vector<vector<char>>& getGrid() const;

    void addBugToBoard(const Bug& bug);
    void displayBoard();
    bool isWayBlocked(const std::pair<int, int>& position, Direction direction) const;
    void tapBoard(const vector<Bug*> & vect);
    void displayAllCells(const vector<Bug*>& bugs) const;
};

#endif //CA2_BUGSLIFE_MICHAL_BECMER_D00256088_BOARD_H