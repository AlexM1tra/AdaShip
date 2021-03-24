//
// Created by Alex on 23/03/2021.
//

#ifndef ADASHIPPROJECT_BOATPOSITION_H
#define ADASHIPPROJECT_BOATPOSITION_H

#include "Coordinate.h"

struct BoatPosition {
    BoatPosition(Coordinate start, Coordinate end);
    std::vector<Coordinate> getCoordinates();
    Coordinate start;
    Coordinate end;
    Direction direction;
};


#endif //ADASHIPPROJECT_BOAT_H