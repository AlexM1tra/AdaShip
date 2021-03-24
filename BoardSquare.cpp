//
// Created by Alex on 03/03/2021.
//

#include "BoardSquare.h"

BoardSquare* BoardSquare::EMPTY() {
    if (!_empty)
        _empty = new BoardSquare("[ ]");
    return _empty;
}

BoardSquare* BoardSquare::BOAT() {
    if (!_boat)
        _boat = new BoardSquare(std::string("[") + "■" + "]");
    return _boat;
}

BoardSquare* BoardSquare::HIT() {
    if (!_hit)
        _hit = new BoardSquare("\033[31m[H]\033[0m");
    return _hit;
}

BoardSquare* BoardSquare::MISS() {
    if (!_miss)
        _miss = new BoardSquare("[M]");
    return _miss;
}

BoardSquare* BoardSquare::MINE() {
    if (!_mine)
        _mine = new BoardSquare("[●]");
    return _mine;
}

BoardSquare::BoardSquare(std::string value) {
    this->_value = std::move(value);
}

std::string BoardSquare::toString() {
    return _value;
}

BoardSquare* BoardSquare::_empty = nullptr;
BoardSquare* BoardSquare::_boat = nullptr;
BoardSquare* BoardSquare::_hit = nullptr;
BoardSquare* BoardSquare::_miss = nullptr;
BoardSquare* BoardSquare::_mine = nullptr;