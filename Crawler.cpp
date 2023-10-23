//
// Created by Gursimar Singh on 24/03/2023.
//

#include <iostream>
#include "Crawler.h"


Crawler::Crawler(int id, pair<int,int> position, int direction, int size , list<pair<int,int>> path) :
            Bug(id, position, direction, size , path) {

    
}


//logic is wrong here will fix later
void Crawler::move() {
    pair<int,int> position = this->getPosition();
    int x = position.first;
    int y = position.second;

    if(isWayBlocked()){
        //give a random direction to the Hopper
        do{
            this->setDirection(rand()%4+1);
        }while(this->isWayBlocked());

    }

        switch (this->getDirection()){
            case NORTH:
                this->setPosition(make_pair(x,y+1));
                break;
            case EAST:
                this->setPosition(make_pair(x+1,y));
                break;
            case SOUTH:
                this->setPosition(make_pair(x,y-1));
                break;
            case WEST:
                this->setPosition(make_pair(x-1,y));
                break;
        }
       //add the position to the path
        this->addPath(this->getPosition());

}



string Crawler::getType() {
    return "Crawler";
}

bool Crawler::isWayBlocked() {

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

ostream& operator<<(ostream& os, const Crawler& crawler) {
    return crawler.display(os);
}

ostream& Crawler::display(ostream& os) const {
    Crawler* c = const_cast<Crawler*>(this);
    os << c->getId() << " Crawler " << c->getPosition().first << "," << c->getPosition().second << " heading " << c->getDirection() << " size " << c->isAlive() << endl;
    return os;
}

