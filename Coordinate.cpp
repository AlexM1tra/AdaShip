//
// Created by Alex on 20/03/2021.
//

#include "Coordinate.h"
#include "Common.h"

Coordinate::Coordinate(std::string name) {
        this->_name = name;
        _setColumnRowFromName(name);
}

Coordinate::Coordinate(int column, int row) {
        this->_column = column;
        this->_row = row;
        this->_name = getColumnFromNumber(column) + std::to_string(row);
}

int Coordinate::Column() const {
        return _column;
}

int Coordinate::Row() const {
    return _row;
}

std::string Coordinate::Name() {
    return _name;
}

std::string Coordinate::getColumnFromNumber(int colNumber) {
    return (colNumber <= 26
            ? std::string() + Common::alphabet[colNumber - 1]
            : std::string() + Common::alphabet[(colNumber - 1) / 26 - 1]
              + Common::alphabet[colNumber % 26 == 0 ? 25 : colNumber % 26 - 1]);
}

std::vector<Coordinate> Coordinate::getConsecutiveCoordinates(Direction direction, int length) {
    std::vector<Coordinate> coordinates;
    switch (direction) {
        case UP:
            for (int row = this->Row(); row > this->Row() - length; row--) {
                coordinates.push_back(Coordinate(this->Column(), row));
            }
            assert(coordinates.size() == length);
            return coordinates;
        case DOWN:
            for (int row = this->Row(); row < this->Row() + length; row++) {
                coordinates.push_back(Coordinate(this->Column(), row));
            }
            assert(coordinates.size() == length);
            return coordinates;
        case LEFT:
            for (int col = this->Column(); col > this->Column() - length; col--) {
                coordinates.push_back(Coordinate(col, this->Row()));
            }
            assert(coordinates.size() == length);
            return coordinates;
        case RIGHT:
            for (int col = this->Column(); col < this->Column() + length; col++) {
                coordinates.push_back(Coordinate(col, this->Row()));
            }
            assert(coordinates.size() == length);
            return coordinates;
    }
    return coordinates;
}

bool Coordinate::operator==(const Coordinate& rhs) const {
    return this->_column == rhs._column && this->_row == rhs._row && this->_name == rhs._name;
}

size_t Coordinate::operator()(Coordinate& c) const {
    return (std::hash<int>()(c.Row())) ^
           (std::hash<int>()(c.Column()));
}

int Coordinate::_columnNumberFromName(std::string col) {
    if (col.size() == 1)
        return Common::alphabet.find(col) + 1;
    return 26 * (Common::alphabet.find(col[0]) + 1) + Common::alphabet.find(col[1]) + 1;
}

void Coordinate::_setColumnRowFromName(std::string name) {
    std::string col, row;
    for (char& i : name) {
        if (isalpha(i))
            col += i;
        else
            row += i;
    }
    this->_row = stoi(row);
    this->_column = _columnNumberFromName(col);
}

std::function<bool(std::string)> Coordinate::isCoordinate = [](std::string input) {
    return input.size() == 2 && isalpha(input[0]) && isdigit(input[1]) // Eg. C4
        || input.size() == 3
            && ((isalpha(input[0]) && isdigit(input[1]) && isdigit(input[2])) // Eg. K13
                || (isalpha(input[0] && isalpha(input[1]) && isdigit(input[2])))) // Eg. AA5
        || input.size() == 4 && isalpha(input[0]) && isalpha(input[1]); // Eg. AD41
};