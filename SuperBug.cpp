//
// Created by Gursimar Singh on 21/04/2023.
//

#include "SuperBug.h"
#include <iostream>

SuperBug::SuperBug(int id, pair<int,int> position, int direction, int size, list<pair<int,int>> path) : Bug(id, position, direction, size, path) {

}

void SuperBug::move() {

    int x = this->getPosition().first;
    int y = this->getPosition().second;

    if (this->isWayBlocked()) {

        do {
            this->setDirection(rand() % 4 + 1);
        } while (this->isWayBlocked());
    }

    switch (this->getDirection()) {
        case NORTH:
            this->setPosition(make_pair(x, y + 1));
            break;
        case EAST:
            this->setPosition(make_pair(x + 1, y));
            break;
        case SOUTH:
            this->setPosition(make_pair(x, y - 1));
            break;
        case WEST:
            this->setPosition(make_pair(x - 1, y));
            break;
    }
    //add the position to the path
    this->addPath(this->getPosition());
}


string SuperBug::getType() {
    return "SuperBug";
}

bool SuperBug::isWayBlocked() {

    //given board is 10x10
    int x = this->getPosition().first;
    int y = this->getPosition().second;

    switch (this->getDirection()){
        case NORTH:
            if(y+1 >= 10){
                return true;
            }
            break;
        case EAST:
            if(x+1 >= 10){
                return true;
            }
            break;
        case SOUTH:
            if(y-1 < 0){
                return true;
            }
            break;
        case WEST:
            if(x-1 < 0){
                return true;
            }
            break;
    }
    return false;

}


ostream& operator<<(ostream& os, const SuperBug& smartBug) {
    return smartBug.display(os);
}

ostream& SuperBug::display(ostream& os) const {

    //get the object
    SuperBug* s = const_cast<SuperBug*>(this);


    os << s->getId() << " SmartBug " << s->getPosition().first << "," << s->getPosition().second << " size:" << s->getSize() << " Heading " << s->getDirection() << endl;

    //distroy the object
    delete s;

    return os;

}