#include <iostream>
#include "Board.h"

using namespace std;

Board::Board(){
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

void Board::tapBoard(const vector<Bug*> &vect){

    for(Bug* bug : vect)
    {
            //if the bug is alive it can move
            if(bug->isAlive())
            {
                bug -> move();
            }
    }
}

void Board::fight(vector<Bug*>& vect) {
    // Iterate through all bugs
    for (auto it = vect.begin(); it != vect.end(); ++it)
    {
        Bug* bug1 = *it;
        // Check if the bug is still alive
        if (!bug1->isAlive())
        {
            continue;
        }
        // Get current bug's position
        pair<int, int> bug1Position = bug1->getPosition();

        // Check for collisions with other bugs
        for (auto otherIt = it + 1; otherIt != vect.end(); ++otherIt)
        {
            Bug* bug2 = *otherIt;
            // Check if the other bug is still alive
            if (!bug2->isAlive())
            {
                continue;
            }
            // Get other bug's position
            pair<int, int> bug2Position = bug2->getPosition();

            // Check if bugs occupy the same position
            if (bug1Position == bug2Position)
            {
                // Resolve conflict
                if (bug1->getSize() > bug2->getSize())
                {
                    // Current bug wins, remove other bug
                    bug2->setAlive(false);
                    cout << "Bug " << bug2->getId() << " has been defeated by Bug " << bug1->getId() << endl;
                }
                else if (bug1->getSize() < bug2->getSize())
                {
                    // Other bug wins, remove current bug
                    bug1->setAlive(false);
                    cout << "Bug " << bug1->getId() << " has been defeated by Bug " << bug2->getId() << endl;
                    break; // Break to avoid further collisions with the defeated bug
                }
                else if (bug1->getSize() == bug2->getSize())
                {
                    int Winner = rand() % 2;
                    if(Winner == 0)
                    {
                        bug2->setAlive(false);
                        cout << "Bug " << bug2->getId() << " has been defeated by Bug " << bug1->getId() << endl;
                    }
                    else
                    {
                        bug1->setAlive(false);
                        cout << "Bug " << bug1->getId() << " has been defeated by Bug " << bug2->getId() << endl;
                    }
                    break;
                }
            }
        }
    }
}

bool Board:: isGameOver(const vector<Bug*>& vect){

    //check the amount of bugs in the vector
    int amountAlive = vect.size();

    for(Bug* bug: vect)
    {
        if(!bug->isAlive())
        {
            amountAlive--;
        }
        if(amountAlive == 1)
        {
            //if there is one bug left, returns true
            return true;
        }
    }
    return false;
}

void Board::displayAllCells(const vector<Bug*>& bugs) const {
    //gets the grid
    const auto& grid = getGrid();

    //loops through each row
    for (int i = 0; i < grid.size(); ++i)
    {
        //loops through each column
        for (int j = 0; j < grid[i].size(); ++j)
        {
            //printing coords of current cell
            cout << "(" << i << ", " << j << "): ";
            bool bugFound = false;
            //looping through bugs to see if it is in a cell
            for (const Bug* bug : bugs)
            {
                //checking if bug is in coords of current cell
                if (bug->getPosition().first == i && bug->getPosition().second == j)
                {
                    cout << "Bug Type: " << bug->getType() << ", ID: " << bug->getId() << " ";
                    bugFound = true;//if bug is found sets it to true
                }
            }
            if (!bugFound)
            {
                //if there is no bug leave it as empty
                cout << "Empty";
            }
            cout << endl;
        }
    }
}

