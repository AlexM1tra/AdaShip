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
    static const std::string you_win;
    static const std::string you_lose;
    static std::string validatedInput(std::string_view prompt, std::function<bool(std::string)> validator, std::string_view errorMessage = "");
    static std::string centerHorizontally(std::string message, int width);
    static std::string centerVertically(std::string message, int height);
    static std::string centerFully(std::string message);
};

#endif //ADASHIPPROJECT_COMMON_H
