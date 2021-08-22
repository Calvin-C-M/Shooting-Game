#include "system.cpp"
#include "map.cpp"
#include "enemy.cpp"
#include "bullet.cpp"

class Player
{
    public:
    int x,y;
    char sprite = 'x';
    int health = 3;
    Bullet bullet;

    void draw()
    {
        Map::ifHitWall(this->x, this->y);
        System::gotoxy(x,y); std::cout << sprite;
    }

    void erase()
        { System::gotoxy(x,y); std::cout << " "; }

    void move(char key)
    {
        switch(key)
        {
            case 'w': this->y--;
                break;

            case 's': this->y++;
                break;

            case 'a': this->x--;
                break;

            case 'd': this->x++;
                break;

            // FIRING KEYS
            case 'i': bullet.draw('u', this->x, this->y, this->sprite);
                break;

            case 'k': bullet.draw('d', this->x, this->y, this->sprite);
                break;

            case 'j': bullet.draw('l', this->x, this->y, this->sprite);
                break;

            case 'l': bullet.draw('r', this->x, this->y, this->sprite);
                break;
        }
    }

    void collisionWithEnemy()
    {
        for(int i=0; i<enemy.total; i++)
        {
            if(this->x == enemy.x[i] && this->y == enemy.y[i])
            {
                this->health--;

                enemy.dead[i] = true;

                // Deleting the enemy (for now)
                enemy.x[i] = 60;
                enemy.y[i] = 60;
                break;
            }
        }
    }

    
};

Player player;