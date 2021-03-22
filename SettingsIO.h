//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_SETTINGSIO_H
#define ADASHIPPROJECT_SETTINGSIO_H

#include <fstream>

#include "Boat.h"

struct BoardDimensions {
    int width;
    int height;
    BoardDimensions(int width, int height) : width(width), height(height) {}
    std::string toString() {
      return std::to_string(width) + "x" + std::to_string(height);
    }
};

class SettingsIO {
public:
    static BoardDimensions currentDimensions();
    static std::pair<BoardDimensions, std::vector<Boat>> getSettings();
    static BoardDimensions readBoardDimensions(std::string dimensions);
    static void updateBoardDimensions(BoardDimensions dimensions);
    static void addBoat(Boat boat);
    static void removeBoat(Boat boat);

    static int screenWidth;
    static int screenHeight;

private:
    static std::vector<std::string> readSettingsFile();
    static void writeToSettingsFile(std::vector<std::string> lines);
    static BoardDimensions boardDimensions;
};

#endif //ADASHIPPROJECT_SETTINGSIO_H

/*
 * There was an issue where the game wasn't finishing as it was supposed to.
 * Some of the boats' remaining spaces weren't being removed.
 * I found out that this was because when looking them up in the coordinate to boat map, their names did not match, they had been set to "".
 * I stepped through the initialisation of the map to make sure that no boats were being added with blank names.
 * I ensured that there was no other interaction with the map apart from reads.
 * In the method that reads, I added an assert to check whether the map contained any blank boats.
 * It did so I added a destructor on the boat class to see when the boat classes were being destroyed.
 * It was called many times at the start (as expected) but then was being called toward the end just before the assertion failed.
 * I realised that the pointer stored in the map was being kept alive but the original object was being destroyed.
 * I migrated the objects to a different list which is now stored in the Board class.
 * The pointers now weren't becoming invalid and the game finished as expected.
 */