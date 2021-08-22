#include "system.cpp"

namespace Map
{
    int yTop=0, yBot=20;
    int xLeft=0, xRight=50;

    void drawBoard()
    {
        for(int i = yTop; i < yBot; i++)
        {
            for(int j = xLeft; j < xRight; j++)
            {
                if(i == yTop || i == yBot-1)
                    { std::cout << "-"; }
                else if(j > 0 && j < xRight-1)
                    { std::cout << " "; }
                else
                    { std::cout << "|"; }
            }
        }
    }

    void ifHitWall(int &x, int &y)
    {
        x += (x == xLeft) ? 1 : 0;
        x -= (x == xRight) ? 1 : 0;
        y += (y == yTop) ? 1 : 0;
        y -= (y == yBot) ? 1 : 0;
    }
}