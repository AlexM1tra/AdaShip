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
    static std::vector<Boat> initialiseSettings();
    static void updateBoardDimensions(BoardDimensions dimensions);
    static void addBoat(Boat boat);
    static void removeBoat(Boat boat);

    static int screenWidth;
    static int screenHeight;
private:
    static BoardDimensions _readBoardDimensions(std::string dimensions);
    static std::vector<std::string> _readSettingsFile();
    static void _writeToSettingsFile(std::vector<std::string> lines);
    static BoardDimensions _boardDimensions;
};

#endif //ADASHIPPROJECT_SETTINGSIO_H