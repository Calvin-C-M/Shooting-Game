/*
    Creator: CALVIN
    Title: Just A Regular Game
    Genre: Action
    Theme: Top View Shooting Game
    Ver: 0.1
*/

#include "game.hpp"

int main()
{
    system("cls");

    bool game = true; // True = game is currently running, false = game stops
    int movementKey = 1; // Number of movement sequences = 4

    drawBoard();
    genEnemy();
    setcursor(0, 0);
    drawPlayer();
    while(game)
    {
        Sleep(100);
        eraseEnemy();
        if(kbhit())
        {
            int key = getch();
            erasePlayer();

            switch(key)
            {
                // Player movements keys
                case 'w':
                    y -= 1;
                break;

                case 's':
                    y += 1;
                break;

                case 'a':
                    x -= 1;
                break;

                case 'd':
                    x += 1;
                break;

                // Firing keys
                case 'i':
                    drawBullet('u');
                break;

                case 'k':
                    drawBullet('d');
                break;

                case 'j':
                    drawBullet('l');
                break;

                case 'l':
                    drawBullet('r');
                break;

                // For easy ending the game
                case 'x':
                    game = false;
                break;
            }

            drawPlayer();
        }

        drawEnemy(movementKey);

        if(collisionPlayer()) // Checks the collision between player and enemy
        {
            game = false;
        }

        if(checkEnemy()) // Checks how many enemies are dead
        {
            game = false;
        }

        gotoxy(30, 30); std::cout << x << ", " << y;
    }
    system("cls");
    gotoxy(0, 0);
    std::cout << "Game Over" << std::endl;
    system("pause");
}