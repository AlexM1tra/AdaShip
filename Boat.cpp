//
// Created by Alex on 02/03/2021.
//

#include "Boat.h"

#include <iostream>

Boat::Boat(std::string_view name, int length) {
    this->_name = name;
    this->_length = length;
    this->spacesNotHit = std::vector<Coordinate>();
}

int Boat::Length() const {
    return this->_length;
}

std::string Boat::Name() const {
    return this->_name;
}

bool Boat::isSunk() {
    return this->spacesNotHit.size() == 0;
}