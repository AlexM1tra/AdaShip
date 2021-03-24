//
// Created by Alex on 23/03/2021.
//

#include "BoatPosition.h"

BoatPosition::BoatPosition(Coordinate start, Coordinate end) : start(start), end(end){
    if (start.Row() != end.Row() && start.Column() == end.Column()) {
        this->direction = (start.Row() < end.Row() ? Direction::DOWN : Direction::UP);
    } else if (start.Column() != end.Column() && start.Row() == end.Row()) {
        this->direction = (start.Column() < end.Column() ? Direction::RIGHT : Direction::LEFT);
    } else {
        this->direction = Direction::UNKNOWN;
    }
}
std::vector<Coordinate> BoatPosition::getCoordinates() {
    std::vector<Coordinate> coordinates;
    switch (this->direction) {
        case Direction::UP:
            for (int row = start.Row(); row >= end.Row(); row--) {
                coordinates.push_back(Coordinate(start.Column(), row));
            }
            return coordinates;
        case Direction::DOWN:
            for (int row = start.Row(); row <= end.Row(); row++) {
                coordinates.push_back(Coordinate(start.Column(), row));
            }
            return coordinates;
        case Direction::LEFT:
            for (int col = start.Column(); col >= end.Column(); col--) {
                coordinates.push_back(Coordinate(col, start.Row()));
            }
            return coordinates;
        case Direction::RIGHT:
            for (int col = start.Column(); col <= end.Column(); col++) {
                coordinates.push_back(Coordinate(col, start.Row()));
            }
            return coordinates;
        case Direction::UNKNOWN:
            coordinates.push_back(start);
            return coordinates;
    }
    return coordinates;
}