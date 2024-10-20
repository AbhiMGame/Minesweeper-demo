#include "Tile.h"
namespace Minesweeper
{
    Tile::Tile()
    {
        m_State = TileState::Hidden;
        m_Type = TileType::Empty;
        m_AdjacentBombCount = -1;
    }
    Tile::~Tile()
    {
    }
    void Tile::Display()
    {
        switch (m_State)
        {
        case TileState::Hidden:
            std::cout << "#";
            break;
        case TileState::Marked:
            std::cout << "O";
            break;
        default:
            DisplayRevealed();
            break;
        }
    }
    void Tile::DisplayRevealed()
    {
        switch (m_Type)
        {
        case TileType::Bomb:
            std::cout << "X";
            break;
        case TileType::Count:
            std::cout << m_AdjacentBombCount;
            break;
        default:
            std::cout << " ";
            break;
        }
    }

    bool Tile::IsState(TileState checkState)
    {
        return m_State == checkState;
    }
    void Tile::SetState(TileState  newState)
    {
        m_State = newState;
    }
    bool Tile::IsType(TileType type)
    {
        return m_Type == type;
    }
    void Tile::SetBomb()
    {
        m_Type = TileType::Bomb;
    }
    void Tile::SetBombCount(int count)
    {
        if (count == 0)
        {
            m_Type = TileType::Empty;
            return;
        }
        m_Type = TileType::Count;
        m_AdjacentBombCount = count;
    }
}