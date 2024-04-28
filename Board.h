#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Board {
protected:
    vector<vector<char>> grid; //Grid for the bug board
    vector<sf::RectangleShape> squares;
public:
    //Constructor
    Board();

    const vector<vector<char>>& getGrid() const;

    void addBugToBoard(const Bug& bug);
    void displayBoard();
    void tapBoard(const vector<Bug*> & vect);
    void displayAllCells(const vector<Bug*>& bugs) const;
    void fight(vector<Bug*>& vect);
    bool isGameOver(const vector<Bug*>& vect);
    void draw(sf::RenderWindow& window, const vector<Bug*>& vect);
};

#endif //CA2_BUGSLIFE_MICHAL_BECMER_D00256088_BOARD_H