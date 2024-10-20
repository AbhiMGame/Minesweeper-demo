#pragma once
#include "Input.h"
#include "Tile.h"

namespace Minesweeper
{
    class Board
    {
    private:
        //Variables
        Vector m_MaxSize;
        Tile** m_Tiles;
        
        int m_BombCount;
        bool b_IsBombPlaced;

        bool b_IsGameOver;
        bool b_IsGameWin;

        int m_UnrevealedCount;
        //Functions
        void InitTiles();
        void DestroyTiles();
        // Checking
        bool CheckProcessAvailable(Input);
        bool CheckState(Vector, TileState);
        bool CheckType(Vector, TileType);
        //GamePlay
        void ProcessMarking(Vector);
        void ProcessReveal(Vector);
        void PlaceBombs(Vector);
        void SetAllAdjacentBombCount();
        int CaculateAdjacentBomb(Vector);
        Vector GetRandomPosition();
        void FloodFill(Vector);
    public:
        // Constructor and destructor
        Board();
        virtual ~Board();
        // Checking 
        bool IsInBounds(Vector);
        bool IsGameOver();
        bool IsGameWon();
        // gameplay
        void Process(Input);
        //Display
        void DisplayBoard();
    };
}