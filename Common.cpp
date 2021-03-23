//
// Created by Alex on 19/03/2021.
//

#include "Common.h"
#include "SettingsIO.h"

const std::string Common::alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const std::string Common::clearScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                                        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                                        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                                        "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

const std::string Common::title = "\n"
                          "  ___   _ _____ _____ _    ___ ___ _  _ ___ ___  ___ \n"
                          " | _ ) /_\\_   _|_   _| |  | __/ __| || |_ _| _ \\/ __|\n"
                          " | _ \\/ _ \\| |   | | | |__| _|\\__ \\ __ || ||  _/\\__ \\\n"
                          " |___/_/ \\_\\_|   |_| |____|___|___/_||_|___|_|  |___/\n";

const std::string Common::miss = "\n"
                                 "  __  __ ___ ___ ___ _ \n"
                                 " |  \\/  |_ _/ __/ __| |\n"
                                 " | |\\/| || |\\__ \\__ \\_|\n"
                                 " |_|  |_|___|___/___(_)\n"
                                 "                       \n\n";

const std::string Common::hit = "\n"
                                "  _  _ ___ _____ _ \n"
                                " | || |_ _|_   _| |\n"
                                " | __ || |  | | |_|\n"
                                " |_||_|___| |_| (_)\n"
                                "                   \n\n";

const std::string Common::hit_and_sunk = "\n"
                                         "  _  _ ___ _____     _     ___ _   _ _  _ _  ___ \n"
                                         " | || |_ _|_   _|  _| |_  / __| | | | \\| | |/ / |\n"
                                         " | __ || |  | |   |_   _| \\__ \\ |_| | .` | ' <|_|\n"
                                         " |_||_|___| |_|     |_|   |___/\\___/|_|\\_|_|\\_(_)\n"
                                         "                                                 \n\n";

const std::string Common::you_win = "\n"
                                    " __   _____  _   _  __      _____ _  _ _ \n"
                                    " \\ \\ / / _ \\| | | | \\ \\    / /_ _| \\| | |\n"
                                    "  \\ V / (_) | |_| |  \\ \\/\\/ / | || .` |_|\n"
                                    "   |_| \\___/ \\___/    \\_/\\_/ |___|_|\\_(_)\n"
                                    "                                         \n\n";

const std::string Common::you_lose = "\n"
                                     " __   _____  _   _   _    ___  ___ ___ _ \n"
                                     " \\ \\ / / _ \\| | | | | |  / _ \\/ __| __| |\n"
                                     "  \\ V / (_) | |_| | | |_| (_) \\__ \\ _||_|\n"
                                     "   |_| \\___/ \\___/  |____\\___/|___/___(_)\n"
                                     "                                         \n\n";

const std::string Common::settings = "\n"
                                     "  ___ ___ _____ _____ ___ _  _  ___ ___ \n"
                                     " / __| __|_   _|_   _|_ _| \\| |/ __/ __|\n"
                                     " \\__ \\ _|  | |   | |  | || .` | (_ \\__ \\\n"
                                     " |___/___| |_|   |_| |___|_|\\_|\\___|___/\n";

const std::string Common::place_boat = "\n"
                                       "  ___ _      _   ___ ___   ___  ___   _ _____ \n"
                                       " | _ \\ |    /_\\ / __| __| | _ )/ _ \\ /_\\_   _|\n"
                                       " |  _/ |__ / _ \\ (__| _|  | _ \\ (_) / _ \\| |  \n"
                                       " |_| |____/_/ \\_\\___|___| |___/\\___/_/ \\_\\_|  \n";

const std::string Common::ai1 = "\n"
                                "    _   ___   _ \n"
                                "   /_\\ |_ _| / |\n"
                                "  / _ \\ | |  | |\n"
                                " /_/ \\_\\___| |_|\n";

const std::string Common::ai2 = "\n"
                                "    _   ___   ___ \n"
                                "   /_\\ |_ _| |_  )\n"
                                "  / _ \\ | |   / / \n"
                                " /_/ \\_\\___| /___|\n";

const std::string Common::player1 = "\n"
                                    "  ___ _      ___   _____ ___   _ \n"
                                    " | _ \\ |    /_\\ \\ / / __| _ \\ / |\n"
                                    " |  _/ |__ / _ \\ V /| _||   / | |\n"
                                    " |_| |____/_/ \\_\\_| |___|_|_\\ |_|\n";

const std::string Common::player2 = "\n"
                                    "  ___ _      ___   _____ ___   ___ \n"
                                    " | _ \\ |    /_\\ \\ / / __| _ \\ |_  )\n"
                                    " |  _/ |__ / _ \\ V /| _||   /  / / \n"
                                    " |_| |____/_/ \\_\\_| |___|_|_\\ /___|\n";

std::string Common::validatedInput(std::string_view prompt, std::function<bool(std::string)> validator, std::string_view errorMessage) {
    std::cout << prompt;
    std::string input = "";
    getline(std::cin, input);
    while (!validator(input)) {
        std::cout << (errorMessage == "" ? prompt : errorMessage);
        getline(std::cin, input);
    }
    return input;
}

std::function<bool(std::string)> Common::isOneOf(std::vector<std::string> options) {
  return [&options](std::string input) {
    return std::find(options.begin(), options.end(), input) != options.end();
  };
}

std::string Common::centerHorizontally(std::string message, int width) {
    if (std::find(message.begin(), message.end(), '\n') == message.end()) {
        return (width - message.size()) / 2 >= 0
            ? std::string((width / 2) - (message.size() / 2), ' ') + message
            : message;
    }
    std::string returnString = "";
    int lPad = -1;
    int firstLineLength = 0;
    std::string buffer = "";
    for (auto c : message) {
        firstLineLength++;
        buffer += c;
        if (c == '\n') {
            if (lPad == -1)
                lPad = (width - firstLineLength) / 2;
            returnString += std::string(lPad >= 0 ? lPad : 0, ' ') + buffer;
            buffer = "";
        }
    }
    return returnString;
}

std::string Common::centerVertically(std::string message, int height) {
    int lines = 0;
    for (auto c : message)
        if (c == '\n')
            lines++;
    return message + std::string((height / 2) - (lines / 2), '\n');
}

std::string Common::centerFully(std::string message) {
    return centerVertically(centerHorizontally(message, SettingsIO::screenWidth), SettingsIO::screenHeight);
}