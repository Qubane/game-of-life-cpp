#include "headers/terminal.h"
#include <conio.h>
#include <cstdio>


// Taken from 'https://stackoverflow.com/a/62485211'
void get_terminal_size(int& width, int& height)
{
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
    height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
#endif // Windows/Linux
}


Terminal::Terminal()
    : m_Width(), m_Height()
{
    get_terminal_size(m_Width, m_Height);
    printf("\x1B[?25l");  // make cursor invisible
}

void Terminal::draw(const Board& board) const
{
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    uint8_t old_value = 255;
    for (uint64_t i = 0; i < (uint64_t)board.width() * board.height(); i++)
    {
        uint8_t cur_value = board.get_cell(i);
        if (old_value != cur_value)
        {
            old_value = cur_value;
            if (cur_value == 1)
                std::printf("\x1B[47m");
            else
                std::printf("\x1B[0m");
        }
        std::printf("  ");
    }
}
