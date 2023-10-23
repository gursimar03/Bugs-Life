//
// Created by Gursimar Singh on 24/03/2023.
//

#ifndef BUGSLIFE_BUG_H
#define BUGSLIFE_BUG_H

#include <utility>
#include <string>
#include <list>

using namespace std;

enum Direction{
    NORTH = 1 ,
    EAST = 2,
    SOUTH = 3,
    WEST = 4,
    NORTHWEST = 5,
    NORTHEAST = 6,
    SOUTHEAST = 7,
    SOUTHWEST = 8
};

class Bug {

protected:
    int id;
    pair<int,int> position;
    int direction;
    int size;
    bool alive;
    int killerId;
    list<pair<int,int>> path;

public:
    Bug(int id, pair<int,int> position,int direction, int size,list<pair<int,int>> path);

    void setAlive(bool alive);
    bool isAlive();
    void setPosition(pair<int,int> position);
    pair<int,int> getPosition();
    int getId();
    int getKillerId();
    void setKillerId(int killerId);
    int getSize();
    void setSize(int size);
    void setDirection(int direction);
    int getDirection();
    void addPath(pair<int,int> position);
    list<pair<int,int>> getPath();

    //pure virtual functions to be implemented by the derived classes
    virtual void move() = 0;
    virtual bool isWayBlocked() = 0;
    virtual string getType() = 0;
    virtual ostream& display(ostream& os) const;
    friend ostream& operator<<(ostream& os, const Bug& bug);
};


#endif //BUGSLIFE_BUG_H
