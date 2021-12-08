/*
This cpp defines "AI" functions.
*/

#include <iostream>
#include "mylib.h"

#define CORNER_NUMBER 4U                // ���������� ����� (� �������� ������ ������)
#define CENTER_NUMBER 4U                // ����������� ��������� ���������� ����� � ������
#define MAX_NOT_CORNER_NUMBER 20U       // ������������ ���������� ��������� ����� � ���� 5x5

// ������� ������ ���� ��
void AI::getMove(Tic_Tac_Toe& structGame)
{
    bool CheckMove = false;

    CheckMove = AI::checkWin(structGame);
    if (!CheckMove && structGame.difficulty > 1)
    {
        CheckMove = AI::interfereWithUser(structGame);
    }
    if (!CheckMove && structGame.difficulty > 1)
    {
        CheckMove = AI::moveToCenter(structGame);
    }
    if (!CheckMove)
    {
        CheckMove = AI::moveToCorner(structGame);
    }
    if (!CheckMove)
    {
        CheckMove = AI::moveToNotCorner(structGame);
    }
}

// ��� �� � �����
bool AI::moveToCenter(Tic_Tac_Toe& structGame)
{
    if (structGame.fieldSize % 2 == 1)
    {
        Coord tmp;

        tmp.x = structGame.fieldSize / 2;
        tmp.y = structGame.fieldSize / 2;

        if (GAME::checkCell(structGame, tmp))
        {
            structGame.gameField[tmp.x][tmp.y] = structGame.ai;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        srand(time(0));
        Coord buf[CENTER_NUMBER];
        size_t n = 0U;
        size_t randNumber = 0U;

        for (unsigned int y = 0U; y < structGame.fieldSize; y++)
        {
            if ((y == structGame.fieldSize / 2 - 1) || (y == structGame.fieldSize / 2))
            {
                for (unsigned int x = 0U; x < structGame.fieldSize; x++)
                {
                    if ((x == structGame.fieldSize / 2 - 1) || (x == structGame.fieldSize / 2))
                    {
                        Coord tmp = { x, y };
                        if (GAME::checkCell(structGame, tmp))
                        {
                            buf[n] = tmp;
                            n++;
                        }
                    }
                }
            }
        }

        if (n > 0)
        {
            randNumber = rand() % n;
            structGame.gameField[buf[randNumber].x][buf[randNumber].y] = structGame.ai;
        }
        else
        {
            return false;
        }

        return true;
    }
}

// ��� �� �� �����
bool AI::moveToCorner(Tic_Tac_Toe& structGame)
{
    srand(time(0));
    Coord buf[CORNER_NUMBER];
    size_t n = 0U;
    size_t randNumber = 0U;

    for (unsigned int y = 0U; y < structGame.fieldSize; y++)
    {
        if (y == 0U || y == structGame.fieldSize - 1)
        {
            for (unsigned int x = 0U; x < structGame.fieldSize; x++)
            {
                if (x == 0U || x == structGame.fieldSize - 1)
                {
                    Coord tmp = { x, y };
                    if (GAME::checkCell(structGame, tmp))
                    {
                        buf[n] = tmp;
                        n++;
                    }
                }
            }
        }
    }

    if (n > 0)
    {
        randNumber = rand() % n;
        structGame.gameField[buf[randNumber].x][buf[randNumber].y] = structGame.ai;
    }
    else
    {
        return false;
    }

    return true;
}

// ��� �� � ������ ����� (�� ����, �� �����)
bool AI::moveToNotCorner(Tic_Tac_Toe& structGame)
{
    srand(time(0));
    Coord buf[MAX_NOT_CORNER_NUMBER];
    size_t n = 0U;
    size_t randNumber = 0U;

    for (unsigned int y = 0U; y < structGame.fieldSize; y++)
    {
        for (unsigned int x = 0U; x < structGame.fieldSize; x++)
        {
            Coord tmp = { x, y };
            if (GAME::checkCell(structGame, tmp))
            {
                buf[n] = tmp;
                n++;
            }
        }
    }

    if (n > 0)
    {
        randNumber = rand() % n;
        structGame.gameField[buf[randNumber].x][buf[randNumber].y] = structGame.ai;
    }
    else
    {
        return false;
    }

    return true;
}

// ��� ��, �������� �������� ������������
bool AI::interfereWithUser(Tic_Tac_Toe& structGame)
{
    for (size_t y = 0U; y < structGame.fieldSize; y++)
    {
        for (size_t x = 0U; x < structGame.fieldSize; x++)
        {
            Coord tmp = { x, y };
            if (GAME::checkCell(structGame, tmp))
            {
                structGame.gameField[x][y] = structGame.user;
                if (GAME::checkGameOver(structGame))
                {
                    structGame.gameField[x][y] = structGame.ai;
                    return true;
                }
                else
                {
                    structGame.gameField[x][y] = Empty;
                }
            }
        }
    }

    return false;
}

// ��� ��, ����������� �� ����� � ���������� ������, � �� � ���������
bool AI::checkWin(Tic_Tac_Toe& structGame)
{
    for (size_t y = 0U; y < structGame.fieldSize; y++)
    {
        for (size_t x = 0U; x < structGame.fieldSize; x++)
        {
            Coord tmp = { x, y };
            if (GAME::checkCell(structGame, tmp))
            {
                structGame.gameField[x][y] = structGame.ai;
                if (GAME::checkGameOver(structGame))
                {
                    return true;
                }
                else
                {
                    structGame.gameField[x][y] = Empty;
                }
            }
        }
    }

    return false;
}
