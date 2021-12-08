/*
This cpp defines "GAME" functions.
*/

#include <iostream>
#include "mylib.h"

#define CLEAR_SCREEN "cls"              // константа для очистки экрана

// инициализация поля с заданным размером
void GAME::InitField(Tic_Tac_Toe& structGame)
{
    structGame.gameField = new (std::nothrow) Symbols * [structGame.fieldSize];
    for (size_t i = 0U; i < structGame.fieldSize; i++)
    {
        structGame.gameField[i] = new (std::nothrow) Symbols[structGame.fieldSize];
    }
    for (size_t y = 0U; y < structGame.fieldSize; y++)
    {
        for (size_t x = 0U; x < structGame.fieldSize; x++)
        {
            structGame.gameField[x][y] = Empty;
        }
    }
}

// уничтожение поля с заданным размером
void GAME::EraseField(Tic_Tac_Toe& structGame)
{
    for (size_t i = 0; i < structGame.fieldSize; i++)
    {
        delete[] structGame.gameField[i];
    }
    delete[] structGame.gameField;
}

// вывод на экран поля для игры
void GAME::PrintField(const Tic_Tac_Toe& structGame)
{
    std::cout << " y\\x  ";
    for (size_t x = 0U; x < structGame.fieldSize; x++)
    {
        std::cout << x + 1 << "   ";
    }

    for (size_t y = 0U; y < structGame.fieldSize; y++)
    {
        std::cout << std::endl << " " << y + 1 << "  | ";
        for (size_t x = 0U; x < structGame.fieldSize; x++)
        {
            std::cout << structGame.gameField[x][y] << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nComputer plays: \'" << structGame.ai << "\'\n    User plays: \'" << structGame.user << "\'\n\n";
}

// очистка экрана
void GAME::ClearScreen()
{
    system(CLEAR_SCREEN);
}

// проверка пустоты ячейки
bool GAME::checkCell(const Tic_Tac_Toe& structGame, Coord checkCoord)
{
    if (structGame.gameField[checkCoord.x][checkCoord.y] == Empty)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// узнать кто играет первым
void GAME::getWhoPlaysFirst(Tic_Tac_Toe& structGame)
{
    srand(time(0));
    unsigned int whoplays = rand() % 2;
    if (whoplays == 0)
    {
        structGame.ai = Cross;
        structGame.user = Zero;
    }
    else
    {
        structGame.ai = Zero;
        structGame.user = Cross;
    }
}

// в зависимости от номера хода даем возможность сходить ИИ или пользователю
void GAME::getMove(Tic_Tac_Toe& structGame)
{
    if (structGame.turns % 2 == 0)
    {
        if (structGame.ai == Cross)
        {
            AI::getMove(structGame);
        }
        else
        {
            USER::getMove(structGame);
        }
    }
    else
    {
        if (structGame.ai == Zero)
        {
            AI::getMove(structGame);
        }
        else
        {
            USER::getMove(structGame);
        }
    }

    structGame.turns++;
}

// узнать закончена ли игра
bool GAME::checkGameOver(Tic_Tac_Toe& structGame)
{
    bool bCheckWin = true;

    // check horizontals
    for (size_t y = 0U; y < structGame.fieldSize; y++)
    {
        bCheckWin = structGame.gameField[0U][y] != Empty;
        for (size_t x = 0U; x < structGame.fieldSize - 1; x++)
        {
            bCheckWin &= (structGame.gameField[x][y] == structGame.gameField[x + 1][y]);
        }
        if (bCheckWin)
        {
            structGame.winner = structGame.gameField[0U][y];
            return true;
        }
    }

    //check verticals
    for (size_t x = 0U; x < structGame.fieldSize; x++)
    {
        bCheckWin = structGame.gameField[x][0U] != Empty;
        for (size_t y = 0U; y < structGame.fieldSize - 1; y++)
        {
            bCheckWin &= (structGame.gameField[x][y] == structGame.gameField[x][y + 1]);
        }

        if (bCheckWin)
        {
            structGame.winner = structGame.gameField[x][0U];
            return true;
        }
    }

    //check main diagonal
    bCheckWin = structGame.gameField[0U][0U] != Empty;
    for (size_t i = 0U; i < structGame.fieldSize - 1; i++)
    {
        bCheckWin &= (structGame.gameField[i][i] == structGame.gameField[i + 1][i + 1]);
    }
    if (bCheckWin)
    {
        structGame.winner = structGame.gameField[0U][0U];
        return true;
    }

    //check side diagonal
    bCheckWin = structGame.gameField[0U][structGame.fieldSize - 1] != Empty;
    for (size_t j = 0; j < structGame.fieldSize - 1; j++)
    {
        bCheckWin &= (structGame.gameField[j][structGame.fieldSize - 1 - j] == structGame.gameField[j + 1][structGame.fieldSize - 1 - (j + 1)]);
    }
    if (bCheckWin)
    {
        structGame.winner = structGame.gameField[0U][2U];
        return true;
    }

    // check draw
    if (structGame.turns == structGame.fieldSize * structGame.fieldSize)
    {
        structGame.winner = Empty;
        return true;
    }

    return false;
}

// узнать какую сложность выбрал пользователь
void GAME::getDifficulty(Tic_Tac_Toe& structGame, const unsigned short int d)
{
    switch (d)
    {
    case 0: structGame.difficulty = Easy; break;
    case 1: structGame.difficulty = Medium; break;
    case 2: structGame.difficulty = Hard; break;
    }
}

// получить от пользователя число, находящееся в диапазоне
void GAME::getNeedableNumber(unsigned short& n, unsigned short MinValue, unsigned short MaxValue, std::string s = "")
{
    bool flag = false;
    do
    {
        std::cout << s;
        std::cin >> n;
        if (n >= MinValue && n <= MaxValue)
        {
            flag = true;
        }
        else
        {
            std::cout << "You wrote incorrect value. Please, try again!\n";
        }
    } while (flag != true);
}

// окончание игры
void GAME::GameOver(Tic_Tac_Toe& structGame)
{
    if (structGame.winner == structGame.user)
    {
        std::cout << "User is the winner!\n";
    }
    else if (structGame.winner == structGame.ai)
    {
        std::cout << "Computer is the winner!\n";
    }
    else
    {
        std::cout << "The game ends by draw!\n";
    }
}
