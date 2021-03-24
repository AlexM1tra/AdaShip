//
// Created by Alex on 02/03/2021.
//

#ifndef ADASHIPPROJECT_COORDINATE_H
#define ADASHIPPROJECT_COORDINATE_H

#include <assert.h>
#include <functional>
#include <string>
#include <vector>

#include "Common.h"

enum Direction {
    UNKNOWN = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 3,
    RIGHT = 4,
};

class Coordinate {
public:
    static std::function<bool(std::string)> isCoordinate;
    static std::string getColumnFromNumber(int colNumber);

    Coordinate(std::string name);
    Coordinate(int column, int row);
    int Column() const;
    int Row() const;
    std::string Name();
    std::vector<Coordinate> getConsecutiveCoordinates(Direction direction, int length);

    bool operator==(const Coordinate& rhs) const;
    size_t operator()(Coordinate& c) const;
private:
    int _columnNumberFromName(std::string col);
    void _setColumnRowFromName(std::string name);
    int _column, _row;
    std::string _name;
};

#endif //ADASHIPPROJECT_COORDINATE_H
