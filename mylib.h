/*
This is the main lib.
*/

#pragma once

// ������������ ��������, ������������ � ����
enum Symbols : char
{
    Cross = 'X',
    Zero = 'O',
    Empty = '_'
};

// ������ ����: � ��������, ������� ������������, ������� ��, �����
enum GameStatus
{
    IN_PROGRESS,
    USER_WON,
    AI_WON,
    DRAW
};

// ������� ���������
enum Difficulty : char
{
    Easy,
    Medium,
    Hard
};

// ���������: ���������
struct Coord
{
    unsigned int x;
    unsigned int y;
};

#pragma pack(push, 1)
// ����� ��������� ����
struct Tic_Tac_Toe
{
    Symbols** gameField;
    GameStatus status;
    size_t turns = 0U;
    Symbols user;
    Symbols ai;
    unsigned short fieldSize;
    Symbols winner;
    Difficulty difficulty;
};
#pragma pack(pop)

// ������������ ���� ��
namespace AI
{
    void getMove(Tic_Tac_Toe&);
    bool moveToCenter(Tic_Tac_Toe&);
    bool moveToCorner(Tic_Tac_Toe&);
    bool moveToNotCorner(Tic_Tac_Toe&);
    bool interfereWithUser(Tic_Tac_Toe&);
    bool checkWin(Tic_Tac_Toe&);
}

// ������������ ���� ������������
namespace USER
{
    void getMove(Tic_Tac_Toe&);
}

// ������������ ���� ����
namespace GAME
{
    void getNeedableNumber(unsigned short&, unsigned short, unsigned short, std::string);

    void InitField(Tic_Tac_Toe&);
    void EraseField(Tic_Tac_Toe&);

    void getDifficulty(Tic_Tac_Toe&, const unsigned short int);
    void getWhoPlaysFirst(Tic_Tac_Toe&);
    void PrintField(const Tic_Tac_Toe&);
    bool checkCell(const Tic_Tac_Toe&, Coord);
    void getMove(Tic_Tac_Toe&);

    bool checkGameOver(Tic_Tac_Toe&);
    void GameOver(Tic_Tac_Toe&);

    void ClearScreen();
}
