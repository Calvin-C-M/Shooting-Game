/*
    Creator: CALVIN
    Title: ???
    Genre: Action
    Theme: Top View Shooting Game
    Ver: 0.2.0
*/

#include "game.hpp"

using namespace System;

void main_menu();
void instructions1();
void high_score(); //STILL IN PROGRESS

int main()
{
    main_menu();
}

void main_menu()
{
    system("cls");

    gotoxy(30, 10); std::cout << "TEST TITLE";
    gotoxy(30, 11); std::cout << "1. Play";
    gotoxy(30, 12); std::cout << "2. How to play";
    gotoxy(30, 13); std::cout << "3. High Score";
    gotoxy(30, 14); std::cout << "4. Exit";

    char key = getch();
    switch(key)
    {
        case '1':
            play();
            main_menu();
        break;

        case '2':
            instructions1();
        break;

        // STILL IN PROGRESS
        // case '3':
            // high_score();
        // break;

        case '4':
            system("cls");
            gotoxy(30, 12);std::cout << "Thank you for playing";
        break;

        default:
            main_menu();
        break;
    }
}

void instructions1()
{
    system("cls");
    gotoxy(55, 11); std::cout << "HOW TO PLAY";
    gotoxy(30, 12); std::cout << "Movement Keys";
    gotoxy(20, 13); std::cout << "w - move up       a - move left";
    gotoxy(20, 14); std::cout << "s - move down     d - move right";
    gotoxy(80, 12); std::cout << "Firing Keys";
    gotoxy(70, 13); std::cout << "i - fire up       j - fire left";
    gotoxy(70, 14); std::cout << "k - fire down     l - fire right";
    // gotoxy(90, 16); std::cout << "> Next Page";

    char key = getch();
    switch(key)
    {
        case 'b':
            main_menu();
        break;

        // case '>':;
        // break;

        default:
            instructions1();
        break;
    }
}

void high_score()
{

}