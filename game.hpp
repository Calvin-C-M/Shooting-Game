#include "system.cpp"
#include "player.cpp"
#include "enemy.cpp"

bool isEnemyAllDead()
{
    int totalOfDeadEnemy=0;
    for(int i=0; i<enemy.total; i++)
    {
        if(enemy.dead[i])
            { totalOfDeadEnemy++; }
    }
    return (totalOfDeadEnemy == enemy.total) ? true : false;
}

void play()
{
    system("cls");

    bool game=true; // True = game is running, false = game stops
    int enemyMovementKey=1; // Number of enemy movement sequences = 4;

    Map::drawBoard();
    enemy.generate();
    player.draw();
    while(game)
    {
        Sleep(100);
        enemy.erase();
        System::gotoxy(60,3); std::cout << "Player x " << player.health;
        if(kbhit())
        {
            char key = getch();
            player.erase();
            player.move(key);
            if(key == 'x')
                { game=false; }

            player.draw();
        }

        enemy.draw(enemyMovementKey);
        player.collisionWithEnemy();

        if(player.health == 0 || isEnemyAllDead())
            { game=false; }
    }
    system("cls");
    System::gotoxy(30,15); std::cout << "Game Over\n";
    Sleep(1000);
}
