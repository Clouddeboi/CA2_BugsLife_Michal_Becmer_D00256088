#ifndef CA2_BUGSLIFE_MICHAL_BECMER_D00256088_CRAWLER_H
#define CA2_BUGSLIFE_MICHAL_BECMER_D00256088_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug{

private:

public:

    Crawler(char type, int id, int x, int y, int direction, int size);

    void move() override;
//    ~Crawler();

};

#endif //CA2_BUGSLIFE_MICHAL_BECMER_D00256088_CRAWLER_H
