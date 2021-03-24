//
// Created by Alex on 02/03/2021.
//

#include "Boat.h"

Boat::Boat(std::string_view name, int length) {
    this->_name = name;
    this->_length = length;
    this->spacesNotHit = std::vector<Coordinate>();
}

bool Boat::isSunk() const {
    return this->spacesNotHit.empty();
}

int Boat::Length() const {
    return this->_length;
}

std::string Boat::Name() const {
    return this->_name;
}