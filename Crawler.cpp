#include <iostream>
#include "Crawler.h"
#include "Board.h"

using namespace std;

Crawler::Crawler(char type, int id, int x, int y, int direction, int size) : Bug(type, id, x , y , direction, size) {}

void Crawler::move() {

    //position before bug has moved
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
                newPos.second--;
                cout << "Moving North" << endl;
                break;
            case Direction::East:
                newPos.first++;
                cout << "Moving East" << endl;
                break;
            case Direction::South:
                newPos.second++;
                cout << "Moving South" << endl;
                break;
            case Direction::West:
                newPos.first--;
                cout << "Moving West" << endl;
                break;
        }
        //update new position and print
        setPosition(newPos);
        getPath().push_back(newPos);

        cout << "New Position: (" << getPosition().first << ", " << getPosition().second << ")\n" << endl;

}