//
// Created by micha on 24/04/2024.
//

#include <iostream>
#include "Hopper.h"
#include "Board.h"

Hopper::Hopper(char type, int id, int x, int y, int direction, int size,
               int hopLength) : Bug(type, id, x,y,direction,size){

    this -> hopLength = hopLength;
    path.push_back(position);
}

void Hopper::move() {

    cout << "Old Position: (" << getPosition().first << ", " << getPosition().second << ")" << endl;

    pair<int, int> newPos = getPosition();
    auto currentDirection = getDirection();

    Board board;

    if (!board.isWayBlocked(newPos, currentDirection)) {

        switch (currentDirection) {
            case Direction::North:
                newPos.second += hopLength;
                break;
            case Direction::East:
                newPos.first += hopLength;
                break;
            case Direction::South:
                newPos.second -= hopLength;
                break;
            case Direction::West:
                newPos.first -= hopLength;
                break;
        }
        //update new position and print
        setPosition(newPos);
        cout << "New Position: (" << getPosition().first << ", " << getPosition().second << ")\n" << endl;
    }
    else
    {
        int randomDir = rand() % 4 + 1;//chooses random direction from 1-4
        setDirection(static_cast<Direction>(randomDir));//sets new direction
        cout << "This Direction is blocked! Redirecting!\n" << endl;
        move(); //recursive function calling move to move after changing direction
    }

}



