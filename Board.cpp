//
// Created by Alex on 02/03/2021.
//

#include "Board.h"

#include <iostream>
#include <assert.h>

Board::Board(int width, int height, std::vector<Boat> boats) {
	this->width = width;
	this->height = height;
	this->boats = boats;
	this->boardMatrix = std::vector<std::vector<BoardSquare*>>(height, std::vector<BoardSquare*>(width, BoardSquare::EMPTY()));
}

std::string Board::getBoardForOwnerAsString() {
	std::string returnString = "  ";
	std::string currentColumn;
	for (int c = 1; c <= this->width; c++) {
	    currentColumn = Coordinate::getColumnFromNumber(c);
	    returnString += " " + currentColumn + (currentColumn.size() == 2 ? "" : " ");
	}
	returnString += "\n";
	for (int row = 0; row < this->height; row++) {
	    returnString +=  std::to_string(row + 1) + (row <= 8 ? " " :  "");
		for (BoardSquare*& item : this->boardMatrix[row]) {
			returnString += item->toString();
		}
		returnString += "\n";
	}
	return returnString;
}

std::string Board::getBoardForOpponentAsString() {
    std::string returnString = "  ";
    std::string currentColumn;
    for (int c = 1; c <= this->width; c++) {
        currentColumn = Coordinate::getColumnFromNumber(c);
        returnString += " " + currentColumn + (currentColumn.size() == 2 ? "" : " ");
    }
    returnString += "\n";
    for (int row = 0; row < this->height; row++) {
        returnString +=  std::to_string(row + 1) + (row <= 8 ? " " :  "");
        for (BoardSquare*& item : this->boardMatrix[row]) {
            if (item != BoardSquare::BOAT())
                returnString += item->toString();
            else
                returnString += BoardSquare::EMPTY()->toString();
        }
        returnString += "\n";
    }
    return returnString;
}

std::string Board::getBoardWithPlacementOptions(std::vector<BoatPosition> options) {
    std::vector<std::vector<std::string>> boardCopy(this->height, std::vector<std::string>(this->width, ""));
    for (int row = 0; row < this->boardMatrix.size(); row++) {
        for (int col = 0; col < this->boardMatrix[row].size(); col++)
            boardCopy[row][col] = this->boardMatrix[row][col]->toString();
    }
    for (int optionNumber = 0; optionNumber < options.size(); optionNumber++) {
        std::vector<Coordinate> optionCoordinates = options[optionNumber].getCoordinates();
        for (int c = 1; c < optionCoordinates.size(); c++) {
            boardCopy[optionCoordinates[c].Row() - 1][optionCoordinates[c].Column() - 1] = "[" + std::to_string(optionNumber + 1) + "]";
        }
    }
    boardCopy[options[0].start.Row() - 1][options[0].start.Column() - 1] = "[■]";

    std::string returnString = "  ";
    std::string currentColumn;
    for (int c = 1; c <= this->width; c++) {
        currentColumn = Coordinate::getColumnFromNumber(c);
        returnString += " " + currentColumn + (currentColumn.size() == 2 ? "" : " ");
    }
    returnString += "\n";
    for (int row = 0; row < this->height; row++) {
        returnString +=  std::to_string(row + 1) + (row <= 8 ? " " :  "");
        for (std::string item : boardCopy[row]) {
            returnString += item;
        }
        returnString += "\n";
    }
    return returnString;
}

BoardSquare* Board::getStatusOfSquare(Coordinate square) {
    return this->boardMatrix[square.Row() - 1][square.Column() - 1];
}

void Board::addBoat(Boat* boat, BoatPosition position) {
    this->unsunkShips.push_back(boat);
    this->fillBoatSquares(position.getCoordinates(), boat);
}

void Board::fillBoatSquares(std::vector<Coordinate> coordinates, Boat* boat) {
    for (Coordinate c : coordinates) {
        this->setStatusOfSquare(c, BoardSquare::BOAT());
        this->coordinateToBoat[c] = boat;
        boat->spacesNotHit.push_back(c);
    }
}

void Board::setStatusOfSquare(Coordinate square, BoardSquare* value) {
    this->boardMatrix[square.Row() - 1][square.Column() - 1] = value;
}

Board::TurnResult Board::attackSquare(Coordinate& square) {
    const BoardSquare* chosenSquare = this->getStatusOfSquare(square);
    if (chosenSquare == BoardSquare::EMPTY()) {
        this->setStatusOfSquare(square, BoardSquare::MISS());
        return TurnResult::MISS;
    }
    else if (chosenSquare == BoardSquare::BOAT()) {
        this->setStatusOfSquare(square, BoardSquare::HIT());
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
        this->setStatusOfSquare(square, BoardSquare::MISS());
        for (int row = square.Row() - 1; row <= square.Row() + 1; row++) {
            for (int col = square.Column() - 1; col <= square.Column() + 1; col++) {
                if (row > 0 && col > 0 && row <= SettingsIO::currentDimensions().height && col <= SettingsIO::currentDimensions().width) {
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
    if (this->coordinateToBoat.find(*c) != this->coordinateToBoat.end())
        return this->coordinateToBoat[*c];
    return nullptr;
}

void Board::clear() {
    this->boardMatrix = std::vector<std::vector<BoardSquare*>>(height, std::vector<BoardSquare*>(width, BoardSquare::EMPTY()));
    this->coordinateToBoat = std::unordered_map<Coordinate, Boat*>();
    this->unsunkShips.clear();
}

void Board::addMines() {
    int minesAdded = 0;
    Coordinate c = Coordinate(1, 1);
    while (minesAdded < 5) {
        c =  Coordinate((rand() % SettingsIO::currentDimensions().width) + 1,
                        (rand() % SettingsIO::currentDimensions().height) + 1);
        if (this->getStatusOfSquare(c) == BoardSquare::EMPTY())
            this->setStatusOfSquare(c, BoardSquare::MINE());
            minesAdded++;
    }
}