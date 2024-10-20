#include "Game.h"
namespace Minesweeper
{
    // Constructor and destructor
    Game::Game(){}
    Game::~Game(){}

    //Functions
    void Game::GetInput()
    {
        std::cout << "Enter Row Index, Column Index, reveal(0)/Mark(1) :\n";
        std::cin >> m_Input.index.y >> m_Input.index.x >> m_Input.isMark;
    }
    bool Game::IsInputValid()
    {
        system("cls");
        if (!m_Board.IsInBounds(m_Input.index))
        {
            std::cout << "Invalid Input. Retry!\n";
            return false;
        }
        return true;
    }
    void Game::ProcessInput()
    {
        m_Board.Process(m_Input);
    }
    bool Game::IsGameOver()
    {
        if (m_Board.IsGameOver())
        {
            std::cout << "\n" 
                << (m_Board.IsGameWon() ? "WIN" : "LOSE") 
                << " !!!\n\n";
            m_Board.DisplayBoard();
            return true;
        }
        return false;
    }

    //Game Loop
    void Game::Run()
    {
        do
        {
            m_Board.DisplayBoard();
            GetInput();
            if (!IsInputValid())
                continue;
            ProcessInput();
        } while (!IsGameOver());
    }
}