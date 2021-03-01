#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <dos.h>
#include <time.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

int enemyX[3], enemyY[3];
char enemy = 'o';
bool dead[3];

int x = 24, y = 9;
char player = 'x';

int bulletX[5], bulletY[5];
char bullets = '.';
bool shooting = false;

void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void drawPlayer();
void erasePlayer();
void drawBoard();
void genEnemy();
void drawBullet(char dir);
bool collisionBullet(int index);
bool collisionPlayer();
bool checkEnemy();
void drawEnemy(int &key);
void eraseEnemy();


void gotoxy(int x, int y) // Sets the cursor position
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);
}

void setcursor(bool visible, DWORD size) // Sets the visibility cursor
{
    if(size == 0)
    {
        size = 20;
    }

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawPlayer()
{
    // If player hits wall
    if(x == 0)
    {
        x += 1;
    }

    if(x == 49) 
    {
        x -= 1;
    }

    if(y == 0) 
    {
        y += 1;
    }

    if(y == 19)
    {
        y -= 1;
    }

    gotoxy(x, y);
    std::cout << player;
}

void erasePlayer()
{
    gotoxy(x, y); std::cout << " ";
}

void drawBoard()
{
    gotoxy(0, 0);

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            if(i == 0 || i == 19)
            {
                std::cout << "-";
            }

            else if(j > 0 && j < 49)
            {
                std::cout << " ";
            }

            else
            {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }
}

void genEnemy()
{
    srand(time(0));
    
    for(int i = 0; i < 3; i++) //ASSUME TOTAL ENEMY = 3
    {
        // Randomizing the enemy spawn point
        enemyX[i] = rand() % 49;
        enemyY[i] = rand() % 19;

        // If the enemy spawns on the wall
        if(enemyX[i] == 0) 
        {
            enemyX[i] += 1;
        }

        if(enemyY[i] == 0)
        {
            enemyY[i] += 1;
        }

        if(enemyX[i] == 49)
        {
            enemyX[i] -= 1;
        }

        if(enemyY[i] == 19)
        {
            enemyY[i] -= 1;
        }
        
        dead[i] = false;
    }

    for(int i = 0; i < 3; i++)
    {
        gotoxy(0, 25 + i);
        std::cout << i + 1 << ". (" << enemyX[i] << ", " << enemyY[i] << ")";
    }
}

void drawBullet(char dir)
{
    bool wallHit = false;
    int keyX = x, keyY = y;
    for(int i = 0; i < 5; i++) 
    {
        gotoxy(bulletX[i - 1], bulletY[i - 1]); std::cout << " ";
        switch(dir)
        {
            case 'u':
                bulletX[i] = keyX;
                bulletY[i] = keyY - i;

                // When bullet hits upper wall
                if(bulletY[i] == 0)
                {
                    bulletY[i] += 1;
                    wallHit = true;
                }
            break;

            case 'd':
                bulletX[i] = keyX;
                bulletY[i] = keyY + i;

                // When bullet hits bottom wall
                if(bulletY[i] == 19)
                {
                    bulletY[i] -= 1;
                    wallHit = true;
                }
            break;
            
            case 'l':
                bulletX[i] = keyX - i - 2;
                bulletY[i] = keyY;

                // When bullet hits/passes the left wall
                if(bulletX[i] <= 0)
                {
                    wallHit = true;
                }
            break;

            case 'r':
                bulletX[i] = keyX + i + 2;
                bulletY[i] = keyY;

                // When bullet hits/passes the right wall
                if(bulletX[i] >= 49)
                {
                    wallHit = true;
                }
            break;
        }

        if(collisionBullet(i))
        {
            for(int j = 0; j < 3; j++)
            {
                if(bulletX[i] == enemyX[j] && bulletY[i] == enemyY[j])
                {
                    dead[j] = true;
                    gotoxy(enemyX[j], enemyY[j]); std::cout << " ";

                    // Deleting the enemy
                    enemyX[j] = 60;
                    enemyY[j] = 60;
                    break;
                }
            }
            break;
        }

        if(wallHit)
        {
            break;
        }
        gotoxy(bulletX[i], bulletY[i]); std::cout << bullets;
        drawPlayer();
        Sleep(20);
    }
    gotoxy(bulletX[4], bulletY[4]); std::cout << " ";
}

// Checks if the bullet hits the enemy
bool collisionBullet(int index)
{
    for(int j = 0; j < 3; j++)
    {
        if(bulletX[index] == enemyX[j] && bulletY[index] == enemyY[j])
        {
            return true;
            break;
        }
    }
    return false;
}

bool collisionPlayer()
{
    for(int i = 0; i < 3; i++)
    {
        if(x == enemyX[i] && y == enemyY[i])
        {
            return true;
            break;
        }
    }
    return false;
}

bool checkEnemy()
{
    int enemyDown = 0;
    for(int i = 0; i < 3; i++)
    {
        if(dead[i])
        {
            enemyDown++;
        }
    }

    if(enemyDown == 3)
    {
        return true;
    }

    else
    {
        return false;
    }
}

// For moving the enemy
void drawEnemy(int &key)
{
    for(int i = 0; i < 3; i++)
    {
        switch(key)
        {
            case 1:

                if(enemyX[i] + 1 == 49) // If enemy moves to the right side wall
                {
                    continue;
                }

                else
                {
                    enemyX[i]++;
                }

                key++;
            break;

            case 2:

                if(enemyY[i] - 1 == 0) // If enemy moves to the upper wall
                {
                    continue;
                }

                else
                {
                    enemyY[i]--;
                }

                key++;
            break;

            case 3:
                if(enemyX[i] - 1 == 0) // If enemy moves to the right side wall
                {
                    continue;
                }

                else
                {
                    enemyX[i]--;
                }

                key++;
            break;

            case 4:
                if(enemyY[i] + 1 == 19) // If enemy moves to the bottom wall
                {
                    continue;
                }

                else
                {
                    enemyY[i]++;
                }

                key = 1; // Resets the movement sequence
            break;
        }

        if(!dead[i])
        {
            gotoxy(enemyX[i], enemyY[i]); std::cout << enemy;
        }
    }
}

void eraseEnemy()
{
    for(int i = 0; i < 3; i++)
    {
        gotoxy(enemyX[i], enemyY[i]); std::cout << " ";
    }
}