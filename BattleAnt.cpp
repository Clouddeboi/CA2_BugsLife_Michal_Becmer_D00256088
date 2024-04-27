#include <iostream>
#include "Board.h"
#include "BattleAnt.h"

using namespace std;

/*  BATTLE BUG BEHAVIOUR
 *
 *  The battle ants are very large, However,
 *  since they are so large it takes so much energy to
 *  move that they get smaller with every turn!
 *
 *  FEATURES OF BATTLE ANT
 *
 *  -size is a minimum of 15 when adding
 *  -They cannot get under a size of 3
 *  -If they eat another bug they grow +1 in size
 *
 * */

BattleAnt ::BattleAnt(char type, int id, int x, int y, int direction, int size) : Bug(type, id, x , y , direction, size){}

void BattleAnt ::move() {

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

    //update new position and set size of bug
    setPosition(newPos);
    getPath().push_back(newPos);
    setSize(getSize());

        //implement getting smaller logic
        if(getSize() > 3)
        {
            //if larger than 3, lose -1 size
            setSize(getSize() - 1);
        }
        else if(getSize() < 3)
        {
            //if lower than 3, gain +1 size
            setSize(getSize() + 1);
        }

        cout << "New Position: (" << getPosition().first << ", " << getPosition().second << ")\n" << endl;
        cout << "Size Decreased!\nCurrent Size: " << getSize() << "\n" << endl;
}