#pragma once
#include <stdint.h>
#include "game.h"


// Taken from 'https://stackoverflow.com/a/62485211'
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux


// Taken from 'https://stackoverflow.com/a/62485211'
void get_terminal_size(int& width, int& height);



class Terminal
{
public:
	Terminal();

	void draw(const Board& board);

	const int width() const { return m_Width; };
	const int height() const { return m_Height; };
private:
	int m_Width, m_Height;
};
