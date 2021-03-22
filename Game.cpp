//
// Created by Alex on 05/03/2021.
//

#include <thread>
#include <chrono>
#include "Game.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
#include "Common.h"

Game::Game(int numberOfPlayers) {
    this->numberOfPlayers = numberOfPlayers;
    srand(time(NULL));
    std::pair<BoardDimensions, std::vector<Boat>> settings = SettingsIO::readSettings();
    availableShips = settings.second;
    isPlayer1Turn = true;
    if (numberOfPlayers == 0) {
        player1 = new AiPlayer(availableShips, settings.first);
        player2 = new AiPlayer(availableShips, settings.first);
    } else if (numberOfPlayers == 1) {
        player1 = new HumanPlayer(availableShips, settings.first);
        player2 = new AiPlayer(availableShips, settings.first);
    } else {
        player1 = new HumanPlayer(availableShips, settings.first);
        player2 = new HumanPlayer(availableShips, settings.first);
    }
}

void Game::Start() {
    Player* activePlayer;
    Player* passivePlayer;
    Coordinate* chosenSquare;
    Board::TurnResult result;
    while (player1->playerBoard.unsunkShips.size() != 0 && player2->playerBoard.unsunkShips.size() != 0) {
        activePlayer = isPlayer1Turn ? player1 : player2;
        passivePlayer = isPlayer1Turn ? player2 : player1;
        activePlayer->showTurnUI(passivePlayer->playerBoard.getBoardForOwnerAsString());
        chosenSquare = activePlayer->move();
        result = passivePlayer->playerBoard.attackSquare(*chosenSquare);
        activePlayer->processTurnResult(result, chosenSquare);
        if (result != Board::TurnResult::ALREADY_ATTACKED)
            isPlayer1Turn = !isPlayer1Turn;
    }
    if (this->numberOfPlayers == 1) {
        std::cout << Common::clearScreen << (player2->playerBoard.unsunkShips.size() == 0 ? Common::you_win : Common::you_lose) << std::endl;
        for (int i = 0; i < 30; i++) {
            std::cout << " " << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    }
    std::cout << player1->playerBoard.getBoardForOwnerAsString() << "\n\n" << player2->playerBoard.getBoardForOwnerAsString();
}