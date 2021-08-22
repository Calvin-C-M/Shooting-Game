#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <vector>

namespace System
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;

    void gotoxy(int x, int y)
    {
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(console, coord);
    }

    void setcursor(bool visible, DWORD size)
    {
        size = (size == 0) ? 20 : 0;

        CONSOLE_CURSOR_INFO lpCursor;
        lpCursor.bVisible = visible;
        lpCursor.dwSize = size;
        SetConsoleCursorInfo(console, &lpCursor);
    }
}