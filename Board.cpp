//
// Created by Alex on 02/03/2021.
//

#include "Board.h"

Board::Board(int width, int height, std::vector<Boat> boats) {
    this->_width = width;
    this->_height = height;
    this->boats = std::move(boats);
    this->_boardMatrix = std::vector<std::vector<BoardSquare*>>(height,
            std::vector<BoardSquare*>(width, BoardSquare::EMPTY()));
}

std::string Board::getBoardForOwnerAsString() {
    return _getBoardForPlayer(/* isOwner= */ true);
}

std::string Board::getBoardForOpponentAsString() {
    return _getBoardForPlayer(/* isOwner= */ false);
}

std::string Board::getBoardWithPlacementOptions(std::vector<BoatPosition> options) {
    std::vector<std::vector<std::string>> boardCopy(this->_height, std::vector<std::string>(this->_width, ""));
    for (int row = 0; row < this->_boardMatrix.size(); row++) {
        for (int col = 0; col < this->_boardMatrix[row].size(); col++)
            boardCopy[row][col] = this->_boardMatrix[row][col]->toString();
    }
    for (int optionNumber = 0; optionNumber < options.size(); optionNumber++) {
        std::vector<Coordinate> optionCoordinates = options[optionNumber].getCoordinates();
        for (int c = 1; c < optionCoordinates.size(); c++) {
            boardCopy[optionCoordinates[c].Row() - 1][optionCoordinates[c].Column() - 1] =
                    "[" + std::to_string(optionNumber + 1) + "]";
        }
    }
    boardCopy[options[0].start.Row() - 1][options[0].start.Column() - 1] = "[■]";

    std::string returnString = "  ";
    std::string currentColumn;
    for (int c = 1; c <= this->_width; c++) {
        currentColumn = Coordinate::getColumnFromNumber(c);
        returnString += " " + currentColumn + (currentColumn.size() == 2 ? "" : " ");
    }
    returnString += "\n";
    for (int row = 0; row < this->_height; row++) {
        returnString +=  std::to_string(row + 1) + (row <= 8 ? " " :  "");
        for (std::string& item : boardCopy[row]) {
            returnString += item;
        }
        returnString += "\n";
    }
    return returnString;
}

void Board::addBoat(Boat* boat, BoatPosition position) {
    this->unsunkShips.push_back(boat);
    this->_fillBoatSquares(position.getCoordinates(), boat);
}

Board::TurnResult Board::attackSquare(Coordinate& square) {
    const BoardSquare* chosenSquare = this->getStatusOfSquare(square);
    if (chosenSquare == BoardSquare::EMPTY()) {
        this->_setStatusOfSquare(square, BoardSquare::MISS());
        return TurnResult::MISS;
    }
    else if (chosenSquare == BoardSquare::BOAT()) {
        this->_setStatusOfSquare(square, BoardSquare::HIT());
        Boat* boatHit = getBoatAtCoordinate(&square);
        if (boatHit != nullptr) {
            for (int i = 0; i < boatHit->spacesNotHit.size(); i++) {
                if (boatHit->spacesNotHit[i].Name() == square.Name()) {
                    boatHit->spacesNotHit.erase(boatHit->spacesNotHit.begin() + i);
                }
            }
            if (boatHit->isSunk()) {
                for (int i = 0; i < this->unsunkShips.size(); i++) {
                    if (this->unsunkShips[i]->Name() == boatHit->Name()) {
                        this->unsunkShips.erase(this->unsunkShips.begin() + i);
                    }
                }
                return TurnResult::HIT_AND_SUNK;
            }
            return TurnResult::HIT;
        }
        return TurnResult::ALREADY_ATTACKED;
    } else if (chosenSquare == BoardSquare::MINE()) {
        this->_setStatusOfSquare(square, BoardSquare::MISS());
        for (int row = square.Row() - 1; row <= square.Row() + 1; row++) {
            for (int col = square.Column() - 1; col <= square.Column() + 1; col++) {
                if (row > 0 && col > 0
                        && row <= SettingsIO::currentDimensions().height
                        && col <= SettingsIO::currentDimensions().width) {
                    Coordinate attack = Coordinate(col, row);
                    this->attackSquare(attack);
                }
            }
        }
        return TurnResult::MINE;
    }
    else // chosenSquare is either HIT() or MISS()
        return TurnResult::ALREADY_ATTACKED;
}

Boat* Board::getBoatAtCoordinate(Coordinate* c) {
    if (this->_coordinateToBoat.find(*c) != this->_coordinateToBoat.end())
        return this->_coordinateToBoat[*c];
    return nullptr;
}

BoardSquare* Board::getStatusOfSquare(Coordinate square) {
    return this->_boardMatrix[square.Row() - 1][square.Column() - 1];
}

void Board::clear() {
    this->_boardMatrix = std::vector<std::vector<BoardSquare*>>(this->_height,
            std::vector<BoardSquare*>(this->_width, BoardSquare::EMPTY()));
    this->_coordinateToBoat = std::unordered_map<Coordinate, Boat*>();
    this->unsunkShips.clear();
}

void Board::addMines() {
    int minesAdded = 0;
    Coordinate c = Coordinate(1, 1);
    while (minesAdded < 5) {
        c =  Coordinate((rand() % SettingsIO::currentDimensions().width) + 1,
                        (rand() % SettingsIO::currentDimensions().height) + 1);
        if (this->getStatusOfSquare(c) == BoardSquare::EMPTY()) {
            this->_setStatusOfSquare(c, BoardSquare::MINE());
            minesAdded++;
        }
    }
}

// Private methods.

std::string Board::_getBoardForPlayer(bool isOwner) {
    std::string returnString = "  ";
    std::string currentColumn;
    for (int c = 1; c <= this->_width; c++) {
        currentColumn = Coordinate::getColumnFromNumber(c);
        returnString += " " + currentColumn + (currentColumn.size() == 2 ? "" : " ");
    }
    returnString += "\n";
    for (int row = 0; row < this->_height; row++) {
        returnString +=  std::to_string(row + 1) + (row <= 8 ? " " :  "");
        for (BoardSquare*& item : this->_boardMatrix[row]) {
            if (item != BoardSquare::BOAT() || isOwner)
                returnString += item->toString();
            else
                returnString += BoardSquare::EMPTY()->toString();
        }
        returnString += "\n";
    }
    return returnString;
}

void Board::_setStatusOfSquare(Coordinate square, BoardSquare* value) {
    this->_boardMatrix[square.Row() - 1][square.Column() - 1] = value;
}

void Board::_fillBoatSquares(std::vector<Coordinate> coordinates, Boat* boat) {
    for (Coordinate c : coordinates) {
        this->_setStatusOfSquare(c, BoardSquare::BOAT());
        this->_coordinateToBoat[c] = boat;
        boat->spacesNotHit.push_back(c);
    }
}