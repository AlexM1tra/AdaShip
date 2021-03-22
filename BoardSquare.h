//
// Created by Alex on 03/03/2021.
//

#ifndef ADASHIPPROJECT_BOARDSQUARE_H
#define ADASHIPPROJECT_BOARDSQUARE_H

#include <string>

class BoardSquare {
public:
    bool operator==(const BoardSquare& rhs) {
        return this->_value == rhs._value;
    }
    std::string toString() {
        return _value;
    }
    static BoardSquare* EMPTY() {
        if (!_empty)
            _empty = new BoardSquare("[ ]");
        return _empty;
    }
    static BoardSquare* BOAT() {
        if (!_boat)
            _boat = new BoardSquare(std::string("[") + "■" + "]");
        return _boat;
    }
    static BoardSquare* HIT() {
        if (!_hit)
            _hit = new BoardSquare("\033[31m[H]\033[0m");
        return _hit;
    }
    static BoardSquare* MISS() {
        if (!_miss)
            _miss = new BoardSquare("[M]");
        return _miss;
    }
private:
    BoardSquare(std::string value) {
        this->_value = std::move(value);
    }
    std::string _value;
    static BoardSquare* _empty;
    static BoardSquare* _boat;
    static BoardSquare* _hit;
    static BoardSquare* _miss;

};

#endif //ADASHIPPROJECT_BOARDSQUARE_H
