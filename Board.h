//
// Created by Alex on 02/03/2021.
//

#ifndef ADASHIPPROJECT_BOARD_H
#define ADASHIPPROJECT_BOARD_H

#include <vector>
#include <unordered_map>
#include "Coordinate.h"
#include "BoardSquare.h"
#include "Boat.h"

namespace std {

    template <>
    struct hash<Coordinate>
    {
        size_t operator()(const Coordinate& c) const {
            return ((hash<int>()(c.Row())
                     ^ (hash<int>()(c.Column()) << 1)) >> 1);
        }
    };
}

class Board {
public:
    enum TurnResult {
        MISS = 0,
        HIT = 1,
        HIT_AND_SUNK = 2,
        ALREADY_ATTACKED = 3,
    };
    Board(int, int, std::vector<Boat>);
    std::string getBoardForOwnerAsString();
    std::string getBoardForOpponentAsString();
    std::string getBoardWithPlacementOptions(std::vector<BoatPosition>);
    BoardSquare* getStatusOfSquare(Coordinate);
    void addBoat(Boat*, BoatPosition);
    TurnResult attackSquare(Coordinate&);
    Boat* getBoatAtCoordinate(Coordinate*);
    std::vector<Boat> boats;
    std::vector<Boat*> unsunkShips;
private:
    int width, height;
    std::vector<std::vector<BoardSquare*>> boardMatrix;
    std::unordered_map<Coordinate, Boat*> coordinateToBoat;
    void setStatusOfSquare(Coordinate, BoardSquare*);
    void fillBoatSquares(std::vector<Coordinate>, Boat*);
};

#endif //ADASHIPPROJECT_BOARD_H
