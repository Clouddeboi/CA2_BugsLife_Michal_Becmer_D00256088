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
};

#endif //CA2_BUGSLIFE_MICHAL_BECMER_D00256088_BOARD_H
