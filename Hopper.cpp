//
// Created by micha on 24/04/2024.
//

#include "Hopper.h"

void Hopper::move() {

}

Hopper::Hopper(char type, int id, int x, int y, int direction, int size,
               int hopLength) : Bug(type, id, x,y,direction,size){

    this -> hopLength = hopLength;
    path.push_back(position);
}


