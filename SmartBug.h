//
// Created by Gursimar Singh on 21/04/2023.
//

#ifndef BUGSLIFE_SMARTBUG_H
#define BUGSLIFE_SMARTBUG_H
#include "Bug.h"
#include "vector"

class SmartBug : public Bug{

public:
    SmartBug(int id, pair<int,int> position, int direction, int size, list<pair<int,int>> path);

    virtual  void move() override;
    virtual string getType() override;
    virtual bool isWayBlocked() override;
    void move(vector<Bug*> bugs);
    virtual ostream& display(ostream& os) const override;
};


#endif //BUGSLIFE_SMARTBUG_H
