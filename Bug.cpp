#include "Bug.h"

using namespace std;

Bug::~Bug() {

}

Bug::Bug(char type, int id, int x, int y, int direction, int size)
        : type(type), id(id), position(x, y), size(size), alive(true), path() {
    // Convert the integer direction to Direction enum
    this->direction = static_cast<Direction>(direction);
}




char Bug::getType() const {
    return type;
}

void Bug::setType(char type) {
    Bug::type = type;
}

int Bug::getId() const {
    return id;
}

void Bug::setId(int id) {
    Bug::id = id;
}

const std::pair<int, int>& Bug::getPosition() const {
    return position;
}

void Bug::setPosition(const std::pair<int, int>& position) {
    Bug::position = position;
}

Direction Bug::getDirection() const {
    return direction;
}

void Bug::setDirection(Direction direction) {
    Bug::direction = direction;
}

int Bug::getSize() const {
    return size;
}

void Bug::setSize(int size) {
    Bug::size = size;
}

bool Bug::isAlive() const {
    return alive;
}

void Bug::setAlive(bool alive) {
    Bug::alive = alive;
}

list<pair<int, int>> &Bug::getPath(){
    return path;
}

void Bug::setPath(const list<pair<int, int>> &path) {
    Bug::path = path;
}

bool Bug::isWayBlocked() {
    switch (direction) {
        case Direction::North:
            return (position.second == 0);          //y axis = 0 the bug is at the top edge
        case Direction::East:
            return (position.first == 9);           //x axis = 9 the bug is at the right edge
        case Direction::South:
            return (position.second == 9);          //y axis = 9 the bug is at the bottom edge
        case Direction::West:
            return (position.first == 0);           //x axis = 0 the bug is at the lef edge
        default:
            return true; //will return true, meaning the path is blocked
    }
}

Bug::Bug() {}

