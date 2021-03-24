//
// Created by Alex on 22/03/2021.
//

#include "SettingsIO.h"

BoardDimensions SettingsIO::currentDimensions() {
    return SettingsIO::_boardDimensions;
}

std::vector<Boat> SettingsIO::initialiseSettings() {
    std::vector<std::string> lines = _readSettingsFile();
    std::vector<Boat> boats;
    BoardDimensions dimensions = _readBoardDimensions(lines[0]);
    lines.erase(lines.begin());
    for (std::string& line : lines) {
        if (line.substr(0, 6) == "Boat: ") {
            int commaPlace = std::find(line.begin(), line.end(), ',') - line.begin();
            boats.push_back(Boat(line.substr(6, commaPlace - 6), stoi(line.substr(commaPlace + 2, line.size() - (commaPlace + 2)))));
        }
    }
    screenWidth = 3 * dimensions.width + 2;
    screenHeight = 2 * dimensions.height + 15;
    _boardDimensions = dimensions;
    return boats;
}

void SettingsIO::updateBoardDimensions(BoardDimensions dimensions) {
    std::vector<std::string> lines = _readSettingsFile();
    lines[0] = "Board: " + std::to_string(dimensions.width) + "x" + std::to_string(dimensions.height);
    _writeToSettingsFile(lines);
    _boardDimensions = dimensions;
}

void SettingsIO::addBoat(Boat boat) {
    std::vector<std::string> lines = _readSettingsFile();
    lines.push_back("Boat: " + boat.Name() + ", " + std::to_string(boat.Length()));
    _writeToSettingsFile(lines);
}

void SettingsIO::removeBoat(Boat boat) {
    std::vector<std::string> lines = _readSettingsFile();
    std::vector<Boat> boats = initialiseSettings();
    for (int i = 0; i < boats.size(); i++) {
        if (boat.Name() == boats[i].Name())
            lines.erase(lines.begin() + i + 1); // Add 1 because first line is board size.
    }
    _writeToSettingsFile(lines);
}

// Private methods.

BoardDimensions SettingsIO::_readBoardDimensions(std::string dimensions) {
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

std::vector<std::string> SettingsIO::_readSettingsFile() {
    std::vector<std::string> lines;
    std::string line;
    std::ifstream Settings;
    Settings.open("adaship_config.ini");
    while (!Settings.eof()) {
        std::getline(Settings, line);
        if (line.size() > 6)
            lines.push_back(line);
    }
    Settings.close();
    return lines;
}

void SettingsIO::_writeToSettingsFile(std::vector<std::string> lines) {
    std::ofstream Settings;
    Settings.open("adaship_config.ini");
    for (auto& line : lines) {
        if (line.size() > 6)
            Settings << line << "\n";
    }
    Settings.close();
}

BoardDimensions SettingsIO::_boardDimensions = BoardDimensions(0, 0);
int SettingsIO::screenWidth = 0;
int SettingsIO::screenHeight = 0;