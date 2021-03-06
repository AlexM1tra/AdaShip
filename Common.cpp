//
// Created by Alex on 19/03/2021.
//

#include "Common.h"

std::string Common::validatedInput(std::string_view prompt, std::function<bool(std::string)> validator, std::string_view errorMessage, bool autoCapitalise) {
    std::cout << prompt;
    std::string input = "";
    getline(std::cin, input);
    if (autoCapitalise)
        for (auto& c : input)
            c = toupper(c);
    while (!validator(input)) {
        std::cout << (errorMessage == "" ? prompt : errorMessage);
        getline(std::cin, input);
        if (autoCapitalise)
            for (auto& c : input)
                c = toupper(c);
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
    for (int l = 0; l < (height - lines) / 2; l++)
        message += "\n";
    return message;
}

const std::string Common::alphabet() {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

const std::string Common::clearScreen() {
    return "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
           "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
           "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
           "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

const std::string Common::title() {
    return "\n"
           "  ___   _ _____ _____ _    ___ ___ _  _ ___ ___  ___ \n"
           " | _ ) /_\\_   _|_   _| |  | __/ __| || |_ _| _ \\/ __|\n"
           " | _ \\/ _ \\| |   | | | |__| _|\\__ \\ __ || ||  _/\\__ \\\n"
           " |___/_/ \\_\\_|   |_| |____|___|___/_||_|___|_|  |___/\n";
}

const std::string Common::miss() {
    return "\n"
           "  __  __ ___ ___ ___ _ \n"
           " |  \\/  |_ _/ __/ __| |\n"
           " | |\\/| || |\\__ \\__ \\_|\n"
           " |_|  |_|___|___/___(_)\n";
}

const std::string Common::hit() {
    return "\n"
           "  _  _ ___ _____ _ \n"
           " | || |_ _|_   _| |\n"
           " | __ || |  | | |_|\n"
           " |_||_|___| |_| (_)\n";
}

const std::string Common::hit_and_sunk() {
    return "\n"
           "  _  _ ___ _____     _     ___ _   _ _  _ _  ___ \n"
           " | || |_ _|_   _|  _| |_  / __| | | | \\| | |/ / |\n"
           " | __ || |  | |   |_   _| \\__ \\ |_| | .` | ' <|_|\n"
           " |_||_|___| |_|     |_|   |___/\\___/|_|\\_|_|\\_(_)\n";
}

const std::string Common::mine() {
    return "\n"
           "  __  __ ___ _  _ ___ _ \n"
           " |  \\/  |_ _| \\| | __| |\n"
           " | |\\/| || || .` | _||_|\n"
           " |_|  |_|___|_|\\_|___(_)\n";
}

const std::string Common::wins() {
    return "\n"
           " __      _____ _  _ ___ _ \n"
           " \\ \\    / /_ _| \\| / __| |\n"
           "  \\ \\/\\/ / | || .` \\__ \\_|\n"
           "   \\_/\\_/ |___|_|\\_|___(_)\n";
}

const std::string Common::settings() {
    return "\n"
           "  ___ ___ _____ _____ ___ _  _  ___ ___ \n"
           " / __| __|_   _|_   _|_ _| \\| |/ __/ __|\n"
           " \\__ \\ _|  | |   | |  | || .` | (_ \\__ \\\n"
           " |___/___| |_|   |_| |___|_|\\_|\\___|___/\n";
}

const std::string Common::place_boat() {
    return "\n"
           "  ___ _      _   ___ ___   ___  ___   _ _____ \n"
           " | _ \\ |    /_\\ / __| __| | _ )/ _ \\ /_\\_   _|\n"
           " |  _/ |__ / _ \\ (__| _|  | _ \\ (_) / _ \\| |  \n"
           " |_| |____/_/ \\_\\___|___| |___/\\___/_/ \\_\\_|  \n";
}

const std::string Common::ai1() {
    return "\n"
           "    _   ___   _ \n"
           "   /_\\ |_ _| / |\n"
           "  / _ \\ | |  | |\n"
           " /_/ \\_\\___| |_|\n";
}

const std::string Common::ai2() {
    return "\n"
           "    _   ___   ___ \n"
           "   /_\\ |_ _| |_  )\n"
           "  / _ \\ | |   / / \n"
           " /_/ \\_\\___| /___|\n";
}

const std::string Common::player1() {
    return "\n"
           "  ___ _      ___   _____ ___   _ \n"
           " | _ \\ |    /_\\ \\ / / __| _ \\ / |\n"
           " |  _/ |__ / _ \\ V /| _||   / | |\n"
           " |_| |____/_/ \\_\\_| |___|_|_\\ |_|\n";
}
const std::string Common::player2() {
    return "\n"
           "  ___ _      ___   _____ ___   ___ \n"
           " | _ \\ |    /_\\ \\ / / __| _ \\ |_  )\n"
           " |  _/ |__ / _ \\ V /| _||   /  / / \n"
           " |_| |____/_/ \\_\\_| |___|_|_\\ /___|\n";
}