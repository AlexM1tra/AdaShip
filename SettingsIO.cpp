//
// Created by Alex on 22/03/2021.
//

#include "SettingsIO.h"

BoardDimensions SettingsIO::currentDimensions() {
  return SettingsIO::boardDimensions;
}

std::pair<BoardDimensions, std::vector<Boat>> SettingsIO::getSettings() {
    std::vector<std::string> lines = readSettingsFile();
    std::vector<Boat> boats;
    BoardDimensions dimensions = readBoardDimensions(lines[0]);
    lines.erase(lines.begin());
    for (std::string& line : lines) {
        if (line.substr(0, 6) == "Boat: ") {
          int commaPlace = std::find(line.begin(), line.end(), ',') - line.begin();
          boats.push_back(Boat(line.substr(6, commaPlace - 6), stoi(line.substr(commaPlace + 2, line.size() - (commaPlace + 2)))));
        }
    }
    screenWidth = 3 * dimensions.width + 2;
    screenHeight = 2 * dimensions.height + 5;
    boardDimensions = dimensions;
    return std::pair<BoardDimensions, std::vector<Boat>>(dimensions, boats);
};

BoardDimensions SettingsIO::readBoardDimensions(std::string dimensions) {
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

void SettingsIO::updateBoardDimensions(BoardDimensions dimensions) {
    std::vector<std::string> lines = readSettingsFile();
    lines[0] = "Board: " + std::to_string(dimensions.width) + "x" + std::to_string(dimensions.height);
    writeToSettingsFile(lines);
    boardDimensions = dimensions;
}

std::vector<std::string> SettingsIO::readSettingsFile() {
    std::vector<std::string> lines;
    std::string line;
    std::ifstream Settings;
    Settings.open("adaship_config.ini");
    while (!Settings.eof()) {
        std::getline(Settings, line);
        lines.push_back(line);
    }
    Settings.close();
    return lines;
}

void SettingsIO::writeToSettingsFile(std::vector<std::string> lines) {
    std::ofstream Settings;
    Settings.open("adaship_config.ini");
    for (auto& line : lines) {
        if (line != "\n")
          Settings << line << "\n";
    }
    Settings.close();
}

BoardDimensions SettingsIO::boardDimensions = BoardDimensions(0, 0);
int SettingsIO::screenWidth = 0;
int SettingsIO::screenHeight = 0;