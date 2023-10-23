//
// Created by Gursimar Singh on 24/03/2023.
//

#ifndef BUGSLIFE_HOPPER_H
#define BUGSLIFE_HOPPER_H

#include "Bug.h"

class Hopper : public Bug {

private:
    int hopLength;

public:

    Hopper(int id, pair<int,int> position,int direction, int size, int hopLength, list<pair<int,int>> path);
    virtual void move() override;
    virtual bool isWayBlocked() override;
    virtual string getType() override;
    void setHopLength(int hopLength);
    int getHopLength();

    virtual ostream& display(ostream& os) const override;
};


#endif //BUGSLIFE_HOPPER_H
