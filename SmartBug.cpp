//
// Created by Gursimar Singh on 21/04/2023.
//

#include "SmartBug.h"
#include <iostream>

SmartBug::SmartBug(int id, pair<int,int> position, int direction, int size, list<pair<int,int>> path) : Bug(id, position, direction, size, path) {

}



string SmartBug::getType() {
    return "SmartBug";
}

bool SmartBug::isWayBlocked() {

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

void SmartBug::move() {

}
void SmartBug::move(vector<Bug*> bugs) {

    Bug* smallestBug = nullptr;
    // Find the smallest bug by comparing their size
    for (int i = 0; i < bugs.size(); i++) {
        if (bugs[i]->getType() != "SmartBug") {
            if (smallestBug == nullptr || bugs[i]->getSize() < smallestBug->getSize()) {
                smallestBug = bugs[i];
            } else if (bugs[i]->getSize() == smallestBug->getSize()) {
                if (bugs[i]->getPosition().first < smallestBug->getPosition().first ||
                    (bugs[i]->getPosition().first == smallestBug->getPosition().first &&
                     bugs[i]->getPosition().second < smallestBug->getPosition().second)) {
                    smallestBug = bugs[i];
                }
            }
        }
    }




    // Calculate the direction to move in
    int direction = 0;
    if (this->getPosition().first < smallestBug->getPosition().first) {
        if (this->getPosition().second < smallestBug->getPosition().second) {
            direction = SOUTHEAST;
        } else if (this->getPosition().second > smallestBug->getPosition().second) {
            direction = NORTHEAST;
        } else {
            direction = EAST;
        }

    } else if (this->getPosition().first > smallestBug->getPosition().first) {
        if (this->getPosition().second < smallestBug->getPosition().second) {
            direction = SOUTHWEST;
        } else if (this->getPosition().second > smallestBug->getPosition().second) {
            direction = NORTHWEST;
        } else {
            direction = WEST;
        }
    } else {
        if (this->getPosition().second < smallestBug->getPosition().second) {
            direction = SOUTH;
        } else if (this->getPosition().second > smallestBug->getPosition().second) {
            direction = NORTH;
        }
    }


        // Move the SmartBug one unit in the calculated direction
        pair<int, int> position = this->getPosition();
        if (direction == NORTH) {
            position.second--;
        } else if (direction == SOUTH) {
            position.second++;
        }
        if (direction == EAST) {
            position.first++;
        } else if (direction == WEST) {
            position.first--;
        }
        if (direction == NORTHEAST) {
            position.first++;
            position.second--;
        } else if (direction == SOUTHEAST) {
            position.first++;
            position.second++;
        } else if (direction == SOUTHWEST) {
            position.first--;
            position.second++;
        } else if (direction == NORTHWEST) {
            position.first--;
            position.second--;
        }
        this->setPosition(position);
        this->addPath(position);
}




ostream& operator<<(ostream& os, const SmartBug& smartBug) {
    return smartBug.display(os);
}

ostream& SmartBug::display(ostream& os) const {

    SmartBug* s = const_cast<SmartBug*>(this);
    os << s->getId() << " SmartBug " << s->getPosition().first << "," << s->getPosition().second << " size:" << s->getSize() << " Heading " << s->getDirection() << endl;

    return os;
}