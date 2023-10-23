//
// Created by Gursimar Singh on 24/03/2023.
//

#include <iostream>
#include "Hopper.h"


Hopper::Hopper(int id, pair<int,int> position, int direction,int size, int hopLength ,  list<pair<int,int>> path) : Bug(id, position, direction, size, path) {
    this->hopLength = hopLength;
}


void Hopper::move(){

    int x = this->getPosition().first;
    int y = this->getPosition().second;

    if(this->isWayBlocked()){

        do{
            this->setDirection(rand()%4+1);
        }while(this->isWayBlocked());
    }


         //move the Hopper
         switch (this->getDirection()){
              case NORTH:
                this->setPosition(make_pair(x,y+this->hopLength));
                break;
              case EAST:
                this->setPosition(make_pair(x+this->hopLength,y));
                break;
              case SOUTH:
                this->setPosition(make_pair(x,y-this->hopLength));
                break;
              case WEST:
                this->setPosition(make_pair(x-this->hopLength,y));
                break;
         }
         //add the position to the path
         this->addPath(this->getPosition());




}

int Hopper::getHopLength() {
    return this->hopLength;
}


bool Hopper::isWayBlocked() {

    //given board is 10x10
    int x = this->getPosition().first;
    int y = this->getPosition().second;

    switch (this->getDirection()){
        case NORTH:
            if(y+ this->hopLength >= 10){
                return true;
            }
            break;
        case EAST:
            if(x+this->hopLength >= 10){
                return true;
            }
            break;
        case SOUTH:
            if(y-this->hopLength < 0){
                return true;
            }
            break;
        case WEST:
            if(x-this->hopLength < 0){
                return true;
            }
            break;
    }
    return false;
}

string Hopper::getType() {
    return "Hopper";
}




ostream& operator<<(ostream& os, const Hopper& hopper) {
    return hopper.display(os);
}

ostream& Hopper::display(ostream& os) const {
    Hopper* h = const_cast<Hopper*>(this);
    os << h->getId() << " Hopper " << h->getPosition().first << "," << h->getPosition().second << " size:" << h->getSize() << " Heading " << h->getDirection() << " Hop Length: " << h->getHopLength() << endl;
    return os;
}


