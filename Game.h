#pragma once
#include <iostream>
#include "Input.h"
#include "Board.h"

namespace Minesweeper
{
    class Game
    {
    private:
        //Variables
        Input m_Input;
        Board m_Board;
        //Functions
        void GetInput();
        bool IsInputValid();
        void ProcessInput();
        bool IsGameOver();

    public:
        // Constructor and destructor
        Game();
        virtual ~Game();

        //Game Loop
        void Run();
    };
}