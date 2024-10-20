#pragma once
namespace Minesweeper
{
    struct Vector
    {
        int x;
        int y;

        bool operator == (Vector const &vector)
        {
            if(x == vector.x && y == vector.y)
                return true;
            return false;
        }
    };

    struct Input
    {
        Vector index;
        bool isMark;
    };
}