#include "system.cpp"
#include "map.cpp"

class Enemy
{
    public:
    int total = 5;
    std::vector<int> x,y,dead;
    char sprite = 'o';

    bool sameSpawnPoint(int index)
    {
        for(int i=0; i<total; i++)
        {
            if(i == index)
                { continue; }
            else if(x[index] == x[i] && y[index] == y[i])
            {
                return true;
                break;
            }
        }
        return false;
    }

    void generate()
    {
        srand(time(NULL));
        
        for(int i = 0; i < total; i++)
        {
            do
            {
                x[i] = rand() % Map::xRight;
                y[i] = rand() % Map::yBot;
            }while(sameSpawnPoint(i));

            Map::ifHitWall(x[i], y[i]);
            dead[i] = false;
        }

        // DEV ONLY CODE
        // Find the position of the enemy
        // for(int i = 0; i < total; i++)
        // {
        //     System::gotoxy(0, 25+i);
        //     std::cout << i+1 << "(" << this->x[i] << ", " << this->y[i] << ")";
        // }
    }

    void draw(int &key)
    {
        for(int i=0; i<total; i++)
        {
            switch(key)
            {
                case 1:
                    this->x[i] += (this->x[i] == Map::xRight) ? 0 : 1;
                    key++;
                    break;

                case 2:
                    this->y[i] -= (this->y[i] == Map::yTop) ? 0 : 1;
                    key++;
                    break;
                
                case 3:
                    this->x[i] -= (this->x[i] == Map::xLeft) ? 0 : 1;
                    key++;
                    break;

                case 4:
                    this->y[i] += (this->y[i] == Map::yBot) ? 0 : 1;
                    key = 1; // Resetting the key sequence
                    break;
            }

            if(!this->dead[i])
            { System::gotoxy(this->x[i], this->y[i]); std::cout << this->sprite; }
        }
    }

    void erase()
    {
        for(int i=0; i<total; i++)
        { System::gotoxy(this->x[i], this->y[i]); std::cout << " "; }
    }
};

Enemy enemy;