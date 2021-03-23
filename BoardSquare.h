//
// Created by Alex on 03/03/2021.
//

#ifndef ADASHIPPROJECT_BOARDSQUARE_H
#define ADASHIPPROJECT_BOARDSQUARE_H

#include <string>

class BoardSquare {
public:
    static BoardSquare* EMPTY();
    static BoardSquare* BOAT();
    static BoardSquare* HIT();
    static BoardSquare* MISS();
    static BoardSquare* MINE();
    std::string toString();

    bool operator==(const BoardSquare& rhs) {
        return this->_value == rhs._value;
    }
private:
    BoardSquare(std::string value);
    std::string _value;
    static BoardSquare* _empty;
    static BoardSquare* _boat;
    static BoardSquare* _hit;
    static BoardSquare* _miss;
    static BoardSquare* _mine;
};

#endif //ADASHIPPROJECT_BOARDSQUARE_H
