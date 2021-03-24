//
// Created by Alex on 02/03/2021.
//

#ifndef ADASHIPPROJECT_BOAT_H
#define ADASHIPPROJECT_BOAT_H

#include "Coordinate.h"

class Boat {
public:
    Boat(std::string_view, int);
    bool isSunk() const;
    int Length() const;
    std::string Name() const;
    std::vector<Coordinate> spacesNotHit;
private:
    std::string _name;
    int _length;

};

#endif //ADASHIPPROJECT_BOAT_H
