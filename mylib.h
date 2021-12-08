/*
This is the main lib.
*/

#pragma once

// перечисление символов, используемых в игре
enum Symbols : char
{
    Cross = 'X',
    Zero = 'O',
    Empty = '_'
};

// статус игры: в процессе, выиграл пользователь, выиграл ИИ, ничья
enum GameStatus
{
    IN_PROGRESS,
    USER_WON,
    AI_WON,
    DRAW
};

// уровень сложности
enum Difficulty : char
{
    Easy,
    Medium,
    Hard
};

// структура: кординаты
struct Coord
{
    unsigned int x;
    unsigned int y;
};

#pragma pack(push, 1)
// общая структура игры
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

// пространство имен ИИ
namespace AI
{
    void getMove(Tic_Tac_Toe&);
    bool moveToCenter(Tic_Tac_Toe&);
    bool moveToCorner(Tic_Tac_Toe&);
    bool moveToNotCorner(Tic_Tac_Toe&);
    bool interfereWithUser(Tic_Tac_Toe&);
    bool checkWin(Tic_Tac_Toe&);
}

// пространство имен пользователя
namespace USER
{
    void getMove(Tic_Tac_Toe&);
}

// пространство имен игры
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
