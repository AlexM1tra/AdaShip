//
// Created by Alex on 19/03/2021.
//

#ifndef ADASHIPPROJECT_COMMON_H
#define ADASHIPPROJECT_COMMON_H

#include <iostream>
#include <string_view>
#include <string>
#include <vector>
#include <functional>

struct Common {
    static const std::string alphabet;
    static const std::string clearScreen;
    static const std::string title;
    static const std::string miss;
    static const std::string hit;
    static const std::string hit_and_sunk;
    static const std::string mine;
    static const std::string wins;
    static const std::string settings;
    static const std::string place_boat;
    static const std::string ai1;
    static const std::string ai2;
    static const std::string player1;
    static const std::string player2;
    static std::string validatedInput(
        std::string_view prompt, 
        std::function<bool(std::string)> validator,
        std::string_view errorMessage = "",
        bool autoCapitalise = false);
    static std::function<bool(std::string)> isOneOf(std::vector<std::string> options);
    static std::string centerHorizontally(std::string message, int width);
    static std::string centerVertically(std::string message, int height);
    static std::string centerFully(std::string message);
};

#endif //ADASHIPPROJECT_COMMON_H
