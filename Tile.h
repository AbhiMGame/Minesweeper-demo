#pragma once
#include <iostream>

namespace Minesweeper
{
    enum class TileState
    {
        Hidden = 0,
        Revealed = 1,
        Marked = 2
    };

    enum class TileType
    {
        Empty = 0,
        Bomb = 1,
        Count = 2
    };

    class Tile
    {
    private:
        // Variables
        TileState m_State;
        TileType m_Type;

        int m_AdjacentBombCount;

        //Functions
        void DisplayRevealed();
    public:
        // Constructor and destructor
        Tile();
        virtual ~Tile();

        void Display();
        bool IsState(TileState);
        void SetState(TileState);
        bool IsType(TileType);
        void SetBomb();
        void SetBombCount(int);
    };
}