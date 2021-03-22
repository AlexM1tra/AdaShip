//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_GAME_H
#define ADASHIPPROJECT_GAME_H

#include <stdlib.h>
#include <time.h>

#include "Player.h"
#include "SettingsIO.h"

class Game {
public:
    Player * player1;
    Player * player2;
    std::vector<Boat> availableShips;
    bool isPlayer1Turn;
    Game(int numberOfPlayers);
    void Start();
private:
    void clearSunkShips();
    int numberOfPlayers;
};

#endif //ADASHIPPROJECT_GAME_H
