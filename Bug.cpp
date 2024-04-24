#include "Bug.h"

using namespace std;

Bug::~Bug() {

}

Bug::Bug(char type, int id,int x,int y, int direction, int size
         )
        : type(type), id(id), position(x,y), size(size), alive(true), path() {}


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

Bug::Bug() {}

