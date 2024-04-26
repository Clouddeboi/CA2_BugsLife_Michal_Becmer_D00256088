#ifndef CA2_BUGSLIFE_MICHAL_BECMER_D00256088_HOPPER_H
#define CA2_BUGSLIFE_MICHAL_BECMER_D00256088_HOPPER_H

#include "Bug.h"

class Hopper : public Bug{

private:

    int hopLength;

public:

    Hopper(char type, int id, int x, int y, int direction, int size, int hopLength);

    void move() override;
//    ~Hopper();

};

#endif //CA2_BUGSLIFE_MICHAL_BECMER_D00256088_HOPPER_H