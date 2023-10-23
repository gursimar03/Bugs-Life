//
// Created by Gursimar Singh on 24/03/2023.
//

#include <iostream>
#include "Bug.h"

Bug::Bug(int id, pair<int,int> position,int direciton, int size, list<pair<int,int>> path) {
    this->id = id;
    this->direction = direciton;
    this->position = position;
    this->size = size;
    this->alive = true;
    this->path = path;
}

void Bug::setAlive(bool alive) {
    this->alive = alive;
}

bool Bug::isAlive() {
    return this->alive;
}

void Bug::setSize(int size) {
    this->size = size;
}

void Bug::setPosition(pair<int,int> position) {
    this->position = position;
}

pair<int,int> Bug::getPosition() {
    return this->position;
}

int Bug::getId() {
    return this->id;
}

int Bug::getSize() {
    return this->size;
}

void Bug::addPath(pair<int,int> position) {
    this->path.push_back(position);
}

list<pair<int,int>> Bug::getPath() {
    return this->path;
}

void Bug::setKillerId(int killerId) {
    this->killerId = killerId;
}

int Bug::getKillerId() {
    return this->killerId;
}

void Bug::setDirection(int direction) {
    this->direction = direction;
}

int Bug::getDirection() {
    return this->direction;
}

ostream& Bug::display(ostream& os) const {
    os << "ID: " << id << endl;
    os << "Position: (" << position.first << "," << position.second << ")" << endl;
    os << "Direction: " << direction << endl;
    os << "Size: " << size << endl;
    os << "Alive: " << alive << endl;
    os << "Path: ";
    for (auto p : path) {
        os << "(" << p.first << "," << p.second << ") ";
    }
    os << endl;
    return os;
}

ostream& operator<<(ostream& os, const Bug& bug) {
    return bug.display(os);
}







