#include "headers/game.hpp"
#include <iostream>


void run()
{
    // Taken from 'https://stackoverflow.com/a/62485211'
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
    int height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    int width = (int)(w.ws_col);
    int height = (int)(w.ws_row);
#endif // Windows/Linux

    // disable cursor visability
    std::cout << "\x1b[?25l";

    // make board
    Board board(width, height);

    for (int i = 0; i < board.m_Size * 0.25f; i++)
        board.set_cell(rand() % board.m_Width, rand() % board.m_Height, 1);

    // game loop
    while (true)
    {
        board.update_clock();
        board.draw_board();
        board.step_simulation();
        Sleep(25);
    }
}
