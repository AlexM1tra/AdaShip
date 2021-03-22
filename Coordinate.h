//
// Created by Alex on 02/03/2021.
//

#ifndef ADASHIPPROJECT_COORDINATE_H
#define ADASHIPPROJECT_COORDINATE_H

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <functional>

class Coordinate {
public:
    Coordinate(std::string name);
    Coordinate(int column, int row);
    int Column() const;
    int Row() const;
    std::string Name();
    static std::string getColumnFromNumber(int colNumber);
    enum Direction {
        UNKNOWN = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4,
    };
    std::vector<Coordinate> getConsecutiveCoordinates(Direction direction, int length);
    bool operator==(const Coordinate& rhs) const;
    size_t operator()(Coordinate& c) const;
    static std::function<bool(std::string)> isCoordinate;
private:
    int _column, _row;
    std::string _name;
    int _columnNumberFromName(std::string col);
    void _setColumnRowFromName(std::string name);
};

#endif //ADASHIPPROJECT_COORDINATE_H
