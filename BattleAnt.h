#ifndef CA2_BUGSLIFE_MICHAL_BECMER_D00256088_BATTLEANT_H
#define CA2_BUGSLIFE_MICHAL_BECMER_D00256088_BATTLEANT_H

#include "Bug.h"
#include "Board.h"

class BattleAnt : public Bug{
private:

public:
    BattleAnt(char type, int id, int x, int y, int direction, int size);

    void move() override;
    //~BattleAnt();
};


#endif //CA2_BUGSLIFE_MICHAL_BECMER_D00256088_BATTLEANT_H