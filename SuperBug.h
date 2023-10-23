//
// Created by Gursimar Singh on 21/04/2023.
//

#ifndef BUGSLIFE_SUPERBUG_H
#define BUGSLIFE_SUPERBUG_H

#include "Bug.h"

class SuperBug : public Bug  {


public:
    SuperBug(int id, pair<int,int> position, int direction, int size, list<pair<int,int>> path);

    virtual void move() override;
    virtual string getType() override;
    virtual bool isWayBlocked() override;
    virtual ostream& display(ostream& os) const override;
};


#endif //BUGSLIFE_SUPERBUG_H
