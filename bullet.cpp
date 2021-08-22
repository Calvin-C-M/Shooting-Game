#include "system.cpp"
#include "map.cpp"
// #include "player.cpp"
#include "enemy.cpp"

class Bullet
{
    public:
    std::vector<int> x,y;
    int ammo=5;
    char sprite = '.';
    bool shooting;

    bool collisionBullet(int index, int &enemyIndex)
    {
        for(int j=0; j<ammo; j++)
        {
            if(this->x[index] == enemy.x[j] && this->y[index] == enemy.y[j])
            {
                enemyIndex=j; 
                return true;
                break;
            }
        }
        return false;
    }

    void draw(char dir, int entityX, int entityY, char entitySprite)
    {
        bool hitWall = false;
        int keyX=entityX, keyY=entityY;
        for(int i=0; i<ammo; i++)
        {
            System::gotoxy(this->x[i-1], this->y[i-1]); std::cout << " "; // Erasing the previous bullet animation

            switch(dir)
            {
                case 'u':
                    x[i] = keyX;
                    y[i] = keyY-i;

                    if(y[i] == Map::yTop)
                    {
                        y[i] += 1;
                        hitWall = true;
                    }
                    break;

                case 'd':
                    x[i] = keyX;
                    y[i] = keyY+i;
                    
                    if(y[i] == Map::yBot)
                    {
                        y[i] -= 1;
                        hitWall = true;
                    }
                    break;

                case 'l':
                    x[i] = keyX-i-2;
                    y[i] = keyY;

                    if(x[i] <= Map::xLeft)
                        { hitWall = true; }
                    break;

                case 'r':
                    x[i] = keyX+i+2;
                    y[i] = keyY;

                    if(x[i] >= Map::xRight)
                        { hitWall = true; }
                    break;
            }

            int enemyIndex; // Key index for enemy that are colliding with the bullet
            if(collisionBullet(i, enemyIndex))
            {
                enemy.dead[enemyIndex] = true;
                System::gotoxy(enemy.x[enemyIndex], enemy.y[enemyIndex]); std::cout << " ";

                // Deleting the enemy (for now)
                enemy.x[enemyIndex] = 60;
                enemy.y[enemyIndex] = 60;

                break; // Breaking the bullet animation loop
            }

            if(hitWall)
                { break; } // Breaking the bullet animation loop

            System::gotoxy(this->x[i], this->y[i]); std::cout << this->sprite;

            // Drawing the player for better animation
            Map::ifHitWall(entityX, entityY);
            System::gotoxy(entityX, entityY); std::cout << entitySprite;

            Sleep(20);
        }
        System::gotoxy(this->x[ammo-1], this->y[ammo-1]); std::cout << " "; // Erasing the last bullet animation
    }
};