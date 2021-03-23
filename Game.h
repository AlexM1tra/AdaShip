//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_GAME_H
#define ADASHIPPROJECT_GAME_H

#include <stdlib.h>
#include <time.h>

#include "Player.h"
#include "SettingsIO.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
#include "Common.h"

class Game {
public:
    Player * player1;
    Player * player2;
    std::vector<Boat> availableShips;
    bool isPlayer1Turn;
    Game(int numberOfPlayers);
    void Start();
    void SalvoStart();
    void StartWithMines();
private:
    std::vector<Coordinate> getMinesFor(Player* player);
    void showWinner();
    int numberOfPlayers;
};

#endif //ADASHIPPROJECT_GAME_H
