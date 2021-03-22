//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_SETTINGSIO_H
#define ADASHIPPROJECT_SETTINGSIO_H

#include <fstream>

#include "Boat.h"

class SettingsIO {
public:
    static struct BoardDimensions {
        int width;
        int height;
        BoardDimensions(int width, int height) : width(width), height(height) {}
    };

    static std::pair<BoardDimensions, std::vector<Boat>> readSettings() {
        std::vector<std::string> lines;
        std::string line;

        std::ifstream Settings;
        Settings.open("adaship_config.ini");
        while (!Settings.eof()) {
            std::getline(Settings, line);
            lines.push_back(line);
        }
        Settings.close();

        std::vector<Boat> boats;
        BoardDimensions dimensions = readBoardDimensions(lines[0]);
        lines.erase(lines.begin());

        for (std::string& line : lines) {
            int commaPlace = std::find(line.begin(), line.end(), ',') - line.begin();
            boats.push_back(Boat(line.substr(6, commaPlace - 6), stoi(line.substr(commaPlace + 2, line.size() - (commaPlace + 2)))));
        }

        return std::pair<BoardDimensions, std::vector<Boat>>(dimensions, boats);
    };

    static BoardDimensions readBoardDimensions(std::string dimensions) {
        bool isSecondNumber = false;
        std::string firstNumber = "", secondNumber = "";
        for (int i = 7; i < dimensions.size(); i++) {
            if (!isSecondNumber) {
                if (dimensions[i] == 'x')
                    isSecondNumber = true;
                else
                    firstNumber += dimensions[i];
            } else {
                secondNumber += dimensions[i];
            }
        }
        return BoardDimensions(stoi(firstNumber), stoi(secondNumber));
    }

    static const int screenWidth = 10*3 + 5;
    static const int screenHeight = 10*2 + 10;
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