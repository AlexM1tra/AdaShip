//
// Created by Alex on 02/03/2021.
//

#ifndef ADASHIPPROJECT_BOARD_H
#define ADASHIPPROJECT_BOARD_H

#include <unordered_map>

#include "BoardSquare.h"
#include "Boat.h"
#include "BoatPosition.h"
#include "Coordinate.h"
#include "SettingsIO.h"

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
        MINE = 4,
    };
    Board(int, int, std::vector<Boat>);
    std::string getBoardForOwnerAsString();
    std::string getBoardForOpponentAsString();
    std::string getBoardWithPlacementOptions(std::vector<BoatPosition>);
    void addBoat(Boat*, BoatPosition);
    TurnResult attackSquare(Coordinate&);
    Boat* getBoatAtCoordinate(Coordinate*);
    BoardSquare* getStatusOfSquare(Coordinate);
    void clear();
    void addMines();
    std::vector<Boat> boats;
    std::vector<Boat*> unsunkShips;
private:
    std::string _getBoardForPlayer(bool isOwner);
    void _setStatusOfSquare(Coordinate, BoardSquare*);
    void _fillBoatSquares(std::vector<Coordinate>, Boat*);
    int _width, _height;
    std::vector<std::vector<BoardSquare*>> _boardMatrix;
    std::unordered_map<Coordinate, Boat*> _coordinateToBoat;
};

#endif //ADASHIPPROJECT_BOARD_H
