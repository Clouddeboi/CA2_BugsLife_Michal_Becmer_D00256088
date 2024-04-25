#include <iostream>
#include "Crawler.h"
#include "Board.h"

using namespace std;

Crawler::Crawler(char type, int id, int x, int y, int direction, int size) : Bug(type, id, x , y , direction, size) {}

void Crawler::move() {

    //position before bug has moved
    cout << "Old Position: (" << getPosition().first << ", " << getPosition().second << ")" << endl;

    pair<int, int> newPos = getPosition();
    auto currentDirection = getDirection();

    //create board obj to check if a way is blocked
    Board board;

    //check if way is blocked
    if(!board.isWayBlocked(newPos, currentDirection))
    {
        //if its clear, move
        switch (currentDirection) {
            case Direction::North:
                newPos.second++;
                cout << "Moving North" << endl;
                break;
            case Direction::East:
                newPos.first++;
                cout << "Moving East" << endl;
                break;
            case Direction::South:
                newPos.second--;
                cout << "Moving South" << endl;
                break;
            case Direction::West:
                newPos.first--;
                cout << "Moving West" << endl;
                break;
        }
        //update new position and print
        setPosition(newPos);
        cout << "New Position: (" << getPosition().first << ", " << getPosition().second << ")\n" << endl;
    }
    else//if the way is blocked
    {
        int randomDir = rand() % 4 + 1;//chooses random direction from 1-4
        setDirection(static_cast<Direction>(randomDir));//sets new direction
        cout<<"This Direction is blocked! Redirecting!\n" << endl;
        move(); //recursive function calling move to move after changing direction
    }
}
