/*
This is the main file of the project Tic-Tac-Toe where the game begins and ends.
*/

#include <iostream>
#include "mylib.h"

int main()
{
    Tic_Tac_Toe aGame;
    bool end_flag = false;
    unsigned short fieldSize;
    unsigned short difficulty;

    GAME::getNeedableNumber(fieldSize, 3, 5, "Enter field size: ");
    aGame.fieldSize = fieldSize;
    GAME::getNeedableNumber(difficulty, 0, 2, "Enter difficulty level (0 - easy, 1 - medium, 2 - hard): ");

    GAME::ClearScreen();
    GAME::InitField(aGame);
    GAME::getWhoPlaysFirst(aGame);
    GAME::PrintField(aGame);
    GAME::getDifficulty(aGame, difficulty);

    // основной цикл игры
    while (end_flag != true)
    {
        GAME::getMove(aGame);
        GAME::ClearScreen();
        GAME::PrintField(aGame);
        end_flag = GAME::checkGameOver(aGame);
    }

    //окончание игры
    GAME::GameOver(aGame);
    GAME::EraseField(aGame);

    return 0;
}
