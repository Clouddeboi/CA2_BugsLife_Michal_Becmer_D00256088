#include "Bug.h"

using namespace std;

Bug::Bug(char type, int id, const pair<int, int>& position, Direction direction, int size, bool alive,
         const list<pair<int, int>>& path)
        : type(type), id(id), position(position), direction(direction), size(size), alive(alive), path(path) {}

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