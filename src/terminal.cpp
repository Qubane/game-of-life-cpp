#include "headers/terminal.h"


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
}

void Terminal::draw(const Board& board)
{
    // implement draw
}
