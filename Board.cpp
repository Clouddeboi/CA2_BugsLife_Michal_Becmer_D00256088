#include <iostream>
#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace std;

Board::Board(){
    //Initialize the grid to be 10x10, empty spaces will have an '-'
    grid.assign(10, vector<char>(10, '-'));

    //goes through each row
    for (int row = 0; row < 10; row++)
    {
        //goes through each column
        for (int column = 0; column < 10; column++)
        {
            //rectangle with shape of size 48x48
            sf::RectangleShape rs(sf::Vector2f(48, 48));
            //makes it green
            rs.setFillColor(sf::Color::Green);
            //gives it a black outline
            rs.setOutlineColor(sf::Color::Black);
            //outline is 2px wide
            rs.setOutlineThickness(2);
            //sets it position on the grid
            rs.setPosition(column*48, row*48);
            squares.push_back(rs);
        }
    }
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

void Board::tapBoard(const vector<Bug*> &vect) {

    for (Bug *bug: vect)
    {
        //if the bug is alive it can move
        if (bug->isAlive())
        {
            bug->move();
        }
    }
}

void Board::fight(vector<Bug*>& vect) {
    // Iterate through all bugs
    for (auto it = vect.begin(); it != vect.end(); ++it)
    {
        Bug* bug1 = *it;
        //Check if the bug is still alive
        if (!bug1->isAlive())
        {
            continue;
        }
        //Get current bug's position
        pair<int, int> bug1Position = bug1->getPosition();

        //Check for collisions with other bugs
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

            //Check if bugs occupy the same position
            if (bug1Position == bug2Position)
            {
                //Resolve conflict
                if (bug1->getSize() > bug2->getSize())
                {
                    //bug1 wins, remove bug2
                    bug2->setAlive(false);
                    cout << "Bug " << bug2->getId() << " has been defeated by Bug " << bug1->getId() << endl;
                    //if the bug is a battle ant it increases it size by 2 to account for the -1 size it will gain next turn
                    if(bug1->getType() == 'B')
                    {
                        bug1->setSize(bug1->getSize()+2);
                        cout << "Bug: " << bug1->getId() << " Sized Increased" << endl;
                    }
                }
                else if (bug1->getSize() < bug2->getSize())
                {
                    //bug2 wins, remove bug1
                    bug1->setAlive(false);
                    cout << "Bug " << bug1->getId() << " has been defeated by Bug " << bug2->getId() << endl;
                    if(bug2->getType() == 'B')
                    {
                        bug2->setSize(bug2->getSize()+2);
                        cout << "Bug: " << bug2->getId() << " Sized Increased" << endl;
                    }
                    break;//Break to avoid further collisions with the defeated bug
                }
                else if (bug1->getSize() == bug2->getSize())
                {
                    //if they are the sam size its a 50\50 who wins
                    int Winner = rand() % 2;
                    if(Winner == 0)
                    {
                        bug2->setAlive(false);
                        cout << "Bug " << bug2->getId() << " has been defeated by Bug " << bug1->getId() << endl;
                        if(bug1->getType() == 'B')
                        {
                            bug1->setSize(bug1->getSize()+2);
                            cout << "Bug: " << bug1->getId() << " Sized Increased" << endl;
                        }
                    }
                    else
                    {
                        bug1->setAlive(false);
                        cout << "Bug " << bug1->getId() << " has been defeated by Bug " << bug2->getId() << endl;
                        if(bug2->getType() == 'B')
                        {
                            bug2->setSize(bug2->getSize()+2);
                            cout << "Bug: " << bug2->getId() << " Sized Increased" << endl;
                        }
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

void Board::draw(sf::RenderWindow &window, const vector<Bug*>& vect) {

    for (sf::RectangleShape rs : squares)
    {
        window.draw(rs);
    }

    for (const Bug* bug : vect)
    {
        sf::CircleShape bugShape(20);

        //Sets the position of the bug shape based on the bug's position on the board
        bugShape.setPosition(bug->getPosition().second * 48, bug->getPosition().first * 48);

        //sets the colour based on bug type
        if (bug->getType() == 'C')
        {
            bugShape.setFillColor(sf::Color::Red);
            if(!bug->isAlive())
            {
                bugShape.setFillColor(sf::Color::Transparent);
            }
        }
        else if (bug->getType() == 'H')
        {
            bugShape.setFillColor(sf::Color::Blue);
            if(!bug->isAlive())
            {
                bugShape.setFillColor(sf::Color::Transparent);
            }
        }
        else if (bug->getType() == 'B')
        {
            bugShape.setFillColor(sf::Color::Black);
            if(!bug->isAlive())
            {
                bugShape.setFillColor(sf::Color::Transparent);
            }
        }
        //Draw the bug shape
        window.draw(bugShape);
    }
}