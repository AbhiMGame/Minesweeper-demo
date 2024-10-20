#include "Board.h"
#include <ctime> 
#include <cstdlib> 
namespace Minesweeper
{
    void Board::InitTiles()
    {
        m_Tiles = new Tile*[m_MaxSize.x]();
        for (int x = 0; x < m_MaxSize.x; x++)
            m_Tiles[x] = new Tile[m_MaxSize.y];
    }
    void Board::DestroyTiles()
    {
        if (m_Tiles == NULL)
            return;

        for (int y = 0; y < m_MaxSize.y; y++)
            delete[] m_Tiles[y];
        delete[] m_Tiles;
    }
    Board::Board()
    {
        m_MaxSize.x = 9;
        m_MaxSize.y = 9;
        m_BombCount = 10;
        b_IsBombPlaced = false;
        b_IsGameOver = false;
        b_IsGameWin = false;
        m_UnrevealedCount = (m_MaxSize.x * m_MaxSize.y);
        InitTiles();
    }
    Board::~Board()
    {
        DestroyTiles();
    }
    // Checking 
    bool Board::IsInBounds(Vector position)
    {
        return position.x >= 0 && 
            position.x < m_MaxSize.x && 
            position.y >= 0 && 
            position.y < m_MaxSize.y;
    }
    bool Board::IsGameOver()
    {
        if (m_UnrevealedCount == m_BombCount)
        {
            b_IsGameOver = true;
            b_IsGameWin = true;
        }
        return b_IsGameOver;
    }
    bool Board::IsGameWon()
    {
        return b_IsGameWin;
    }
    bool Board::CheckProcessAvailable(Input input)
    {
        Vector pos = input.index;
        if (CheckState(pos,TileState::Revealed))
        {
            std::cout << "Already revealed\n";
            return false;
        }
        // to check if the request is to reveal a marked tile
        if (!input.isMark && CheckState(pos, TileState::Marked))
        {
            std::cout << "Marked Tile\n";
            return false;
        }
        return true;
    }
    bool Board::CheckState(Vector pos, TileState state)
    {
        return m_Tiles[pos.x][pos.y].IsState(state);
    }
    bool Board::CheckType(Vector pos, TileType type)
    {
        return m_Tiles[pos.x][pos.y].IsType(type);
    }

    //Gameplay
    void Board::Process(Input input)
    {
        if (!CheckProcessAvailable(input))
        {
            std::cout << "Process Not Possible\n";
            return;
        }

        if (input.isMark)
        {
            ProcessMarking(input.index);
            return;
        }
        ProcessReveal(input.index);
    }
    void Board::ProcessMarking(Vector pos)
    {
        if (CheckState(pos, TileState::Marked))
            m_Tiles[pos.x][pos.y].SetState(TileState::Hidden);
        else
            m_Tiles[pos.x][pos.y].SetState(TileState::Marked);
    }
    void Board::ProcessReveal(Vector pos)
    {
        m_Tiles[pos.x][pos.y].SetState(TileState::Revealed);
        m_UnrevealedCount--;
        if (!b_IsBombPlaced)
        {
            PlaceBombs(pos);
            SetAllAdjacentBombCount();
        }
        if (CheckType(pos, TileType::Empty))
            FloodFill(pos);
        
        if (CheckType(pos, TileType::Bomb))
        {
            b_IsGameOver = true;
            b_IsGameWin = false;
        }

    }
    void Board::PlaceBombs(Vector firstPos)
    {
        srand(time(0));
        Vector randomPos = firstPos;
        for (int i = 0; i < m_BombCount; i++)
        {
            while (randomPos == firstPos || CheckType(randomPos,TileType::Bomb))
                randomPos = GetRandomPosition();

            m_Tiles[randomPos.x][randomPos.y].SetBomb();
        }
        b_IsBombPlaced = true;
    }
    void Board::SetAllAdjacentBombCount()
    {
        Vector current;
        for (int x = 0; x < m_MaxSize.x; x++)
        {
            for (int y = 0; y < m_MaxSize.y; y++)
            {
                current.x = x;
                current.y = y;
                if (!CheckType(current, TileType::Bomb))
                    m_Tiles[x][y].SetBombCount(CaculateAdjacentBomb(current));
            }
        }
    }
    int Board::CaculateAdjacentBomb(Vector pos)
    {
        Vector index;
        int count = 0;
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                index.x = pos.x + i;
                index.y = pos.y + j;
                if (IsInBounds(index))
                {
                    if (CheckType(index,TileType::Bomb))
                        count++;
                }
            }
        }
        return count;
    }
    Vector Board::GetRandomPosition()
    {
        Vector randompos;
        randompos.x = rand() % m_MaxSize.x;
        randompos.y = rand() % m_MaxSize.y;
        return randompos;
    }

    void Board::FloodFill(Vector pos)
    {
        Vector index;
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                index.x = pos.x + i;
                index.y = pos.y + j;
                if (!IsInBounds(index))
                    continue;

                if (CheckState(index, TileState::Revealed))
                    continue;

                m_Tiles[index.x][index.y].SetState(TileState::Revealed);
                m_UnrevealedCount--;
                if(CheckType(index,TileType::Empty))
                    FloodFill(index);
            }
        }
    }

    //Display
    void Board::DisplayBoard()
    {
        std::cout << " |";
        for (int x = 0; x < m_MaxSize.x; x++)
            std::cout << x << "|";
        std::cout << "\n";
        for (int y = 0; y < m_MaxSize.y; y++)
        {
            std::cout << y << "|";
            for (int x = 0; x < m_MaxSize.x; x++)
            {		
                m_Tiles[x][y].Display();
                std::cout << "|";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "Unrevealed : " << m_UnrevealedCount << "\n";
        std::cout << "Bombs : " << m_BombCount << "\n";
    }
}