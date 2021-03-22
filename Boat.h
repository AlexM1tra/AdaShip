//
// Created by Alex on 02/03/2021.
//

#ifndef ADASHIPPROJECT_BOAT_H
#define ADASHIPPROJECT_BOAT_H

#include <string>
#include "Coordinate.h"

struct BoatPosition {
    Coordinate start;
    Coordinate end;
    Coordinate::Direction direction;
    BoatPosition(Coordinate start, Coordinate end) : start(start), end(end){
        if (start.Row() != end.Row() && start.Column() == end.Column()) {
            this->direction = (start.Row() < end.Row() ? Coordinate::DOWN : Coordinate::UP);
        } else if (start.Column() != end.Column() && start.Row() == end.Row()) {
            this->direction = (start.Column() < end.Column() ? Coordinate::RIGHT : Coordinate::LEFT);
        } else {
            this->direction = Coordinate::UNKNOWN;
        }
    }
    std::vector<Coordinate> getCoordinates() {
        std::vector<Coordinate> coordinates;
        switch (this->direction) {
            case Coordinate::UP:
                for (int row = start.Row(); row >= end.Row(); row--) {
                    coordinates.push_back(Coordinate(start.Column(), row));
                }
                return coordinates;
            case Coordinate::DOWN:
                for (int row = start.Row(); row <= end.Row(); row++) {
                    coordinates.push_back(Coordinate(start.Column(), row));
                }
                return coordinates;
            case Coordinate::LEFT:
                for (int col = start.Column(); col >= end.Column(); col--) {
                    coordinates.push_back(Coordinate(col, start.Row()));
                }
                return coordinates;
            case Coordinate::RIGHT:
                for (int col = start.Column(); col <= end.Column(); col++) {
                    coordinates.push_back(Coordinate(col, start.Row()));
                }
                return coordinates;
            case Coordinate::UNKNOWN:
              coordinates.push_back(start);
              return coordinates;
        }
        return coordinates;
    }
};

class Boat {
public:
    Boat(std::string_view, int);
    std::vector<Coordinate> spacesNotHit;
    bool isSunk();
    int Length() const;
    std::string Name() const;
private:
    std::string _name;
    int _length;

};

#endif //ADASHIPPROJECT_BOAT_H
