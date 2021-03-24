//
// Created by Alex on 05/03/2021.
//

#ifndef ADASHIPPROJECT_GAME_H
#define ADASHIPPROJECT_GAME_H

#include <thread>
#include <chrono>

#include "Player.h"
#include "SettingsIO.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
#include "Common.h"

class Game {
public:
    Game(int numberOfPlayers);
    void start();
    void salvoStart();
    void startWithMines();
private:
    void _showWinner();
    Player* _player1;
    Player* _player2;
};

#endif //ADASHIPPROJECT_GAME_H
