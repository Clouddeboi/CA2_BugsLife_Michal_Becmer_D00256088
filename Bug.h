#ifndef BUG_H
#define BUG_H

#include "Direction.h"
#include <list>
#include <utility>

using namespace std;

class Bug {

protected:
    char type; // Type of bug
    int id; // Identification number
    pair<int,int> position; // Position coordinates
    Direction direction; // Direction the bug is facing
    int size; // Size of the bug
    bool alive; // Flag indicating if the bug is alive
    list<pair<int,int>> path; // Path taken by the bug
    bool isWayBlocked();

public:

    virtual void move() =0;
    virtual ~Bug();

    Bug(char type, int id, int x, int y, int direction, int size);

    Bug();

    char getType() const;

    void setType(char type);

    int getId() const;

    void setId(int id);

    const pair<int, int>& getPosition() const;

    void setPosition(const pair<int, int>& position);

    Direction getDirection() const;

    void setDirection(Direction direction);

    int getSize() const;

    void setSize(int size);

    bool isAlive() const;

    void setAlive(bool alive);

    list<pair<int, int>> &getPath();

    void setPath(const list<pair<int, int>> &path);
};

#endif // BUG_H