//
// Created by Gursimar Singh on 24/03/2023.
//

#ifndef BUGSLIFE_CRAWLER_H
#define BUGSLIFE_CRAWLER_H

#include "Bug.h"

class Crawler : public Bug  {


public:
    Crawler(int id, pair<int,int> position, int direction, int size, list<pair<int,int>> path);

    virtual void move() override;
    virtual string getType() override;
    virtual bool isWayBlocked() override;
    virtual ostream& display(ostream& os) const override;
};


#endif //BUGSLIFE_CRAWLER_H
