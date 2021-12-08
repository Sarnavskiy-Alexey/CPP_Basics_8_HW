/*
This cpp defines "USER" functions.
*/

#include <iostream>
#include "mylib.h"

// позволяет пользователю ходить
void USER::getMove(Tic_Tac_Toe& structGame)
{
    bool flag = false;
    Coord tmp;

    do
    {
        std::cout << "Enter coordinate x: ";
        std::cin >> tmp.x;
        std::cout << "Enter coordinate y: ";
        std::cin >> tmp.y;

        if ((tmp.x > structGame.fieldSize || tmp.y > structGame.fieldSize) ||
            (tmp.x == 0U || tmp.y == 0U))
        {
            std::cout << "You wrote incorrect cell! Please, try again!\n";
            flag = false;
        }
        else
        {
            tmp.x--;
            tmp.y--;
            flag = GAME::checkCell(structGame, tmp);
            if (flag == false)
            {
                std::cout << "This cell is not empty! Please, try again!\n";
            }
        }
    } while (flag != true);

    structGame.gameField[tmp.x][tmp.y] = structGame.user;
}
