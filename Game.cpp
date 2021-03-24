//
// Created by Alex on 05/03/2021.
//

#include "Game.h"

Game::Game(int numberOfPlayers) {
    srand(time(NULL));
    std::vector<Boat> availableShips = SettingsIO::initialiseSettings();
    if (numberOfPlayers == 0) {
        _player1 = new AiPlayer(availableShips, Player::PlayerType::AI1);
        _player2 = new AiPlayer(availableShips, Player::PlayerType::AI2);
    } else if (numberOfPlayers == 1) {
        _player1 = new HumanPlayer(availableShips, Player::PlayerType::PLAYER1);
        _player2 = new AiPlayer(availableShips, Player::PlayerType::AI1);
    } else {
        _player1 = new HumanPlayer(availableShips, Player::PlayerType::PLAYER1);
        _player2 = new HumanPlayer(availableShips, Player::PlayerType::PLAYER2);
    }
}

void Game::start() {
    Player* activePlayer;
    Player* passivePlayer;
    bool is_player1Turn = true;
    Coordinate* chosenSquare;
    Board::TurnResult result;
    std::string resultAsString;
    while (_player1->playerBoard.unsunkShips.size() != 0 && _player2->playerBoard.unsunkShips.size() != 0) {
        activePlayer = is_player1Turn ? _player1 : _player2;
        passivePlayer = is_player1Turn ? _player2 : _player1;
        activePlayer->showTurnUI(passivePlayer->playerBoard.getBoardForOwnerAsString());
        chosenSquare = activePlayer->move();
        if (chosenSquare == nullptr)
            return;
        result = passivePlayer->playerBoard.attackSquare(*chosenSquare);
        activePlayer->processTurnResult(result, chosenSquare);
        if (result != Board::TurnResult::ALREADY_ATTACKED) {
            is_player1Turn = !is_player1Turn;
            activePlayer->showTurnUI(passivePlayer->playerBoard.getBoardForOwnerAsString());
            resultAsString = (result == Board::TurnResult::MISS ? "Miss"
                                                                : result == Board::TurnResult::HIT ? "Hit"
                                                                                                   : result == Board::TurnResult::HIT_AND_SUNK ? "Hit & Sunk"
                                                                                                                                               : "Mine");
            std::cout << "\n" << chosenSquare->Name() << ": " << resultAsString << "\n\nPress [Enter] to end turn...";
            getline(std::cin, resultAsString);
        }
    }
    this->_showWinner();
}

void Game::salvoStart() {
    Player* activePlayer;
    Player* passivePlayer;
    bool is_player1Turn = true;
    Coordinate* chosenSquare;
    std::string goResult = "";
    Board::TurnResult result;
    while (_player1->playerBoard.unsunkShips.size() != 0 && _player2->playerBoard.unsunkShips.size() != 0) {
        activePlayer = is_player1Turn ? _player1 : _player2;
        passivePlayer = is_player1Turn ? _player2 : _player1;
        for (int gos = 0; gos < activePlayer->playerBoard.unsunkShips.size();) {
            activePlayer->showTurnUI(passivePlayer->playerBoard.getBoardForOwnerAsString());
            chosenSquare = activePlayer->move();
            if (chosenSquare == nullptr)
                return;
            result = passivePlayer->playerBoard.attackSquare(*chosenSquare);
            activePlayer->processTurnResult(result, chosenSquare);
            if (result != Board::TurnResult::ALREADY_ATTACKED) {
                gos++;
                goResult += chosenSquare->Name() + ": "
                            + (result == Board::TurnResult::MISS ? "Miss"
                                                                 : result == Board::TurnResult::HIT ? "Hit"
                                                                                                    : "Hit & Sunk") + ", ";
            }
        }
        is_player1Turn = !is_player1Turn;
        activePlayer->showTurnUI(passivePlayer->playerBoard.getBoardForOwnerAsString());
        std::cout << "\n" << goResult.substr(0, goResult.size() - 2) << "\n\nPress [Enter] to end turn...";
        getline(std::cin, goResult);
        goResult = "";
    }
    this->_showWinner();
}

void Game::startWithMines() {
    _player1->playerBoard.addMines();
    _player2->playerBoard.addMines();
    this->start();
}

void Game::_showWinner() {
    std::string winnerName = (_player1->playerBoard.unsunkShips.size() == 0 ? _player2->getName() : _player1->getName());
    std::cout << Common::clearScreen() << winnerName << Common::wins() << std::endl;
    for (int i = 0; i < 30; i++) {
        std::cout << " " << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}