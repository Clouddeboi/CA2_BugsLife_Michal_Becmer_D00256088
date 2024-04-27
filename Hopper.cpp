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

    //check if way is blocked
    while(isWayBlocked())
    {
        cout << "Path Obstructed! Redirecting..." <<endl;
        direction = static_cast<Direction>(1 + (rand() % 4));
    }

    //if its clear, move
    switch (direction) {
        case Direction::North:
            newPos.second-= hopLength;
            if(newPos.second < 0) newPos.second = 0;
            cout << "Moving North" << endl;
            break;
        case Direction::East:
            newPos.first+=hopLength;
            if(newPos.first > 9) newPos.first = 9;
            cout << "Moving East" << endl;
            break;
        case Direction::South:
            newPos.second+=hopLength;
            if(newPos.second > 9) newPos.second = 9;
            cout << "Moving South" << endl;
            break;
        case Direction::West:
            newPos.first-=hopLength;
            if(newPos.first < 0) newPos.first = 0;
            cout << "Moving West" << endl;
            break;
    }
        //update new position and print
        setPosition(newPos);
        getPath().push_back(newPos);
        cout << "New Position: (" << getPosition().first << ", " << getPosition().second << ")\n" << endl;



}


