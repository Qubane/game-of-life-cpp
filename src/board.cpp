#include "headers/game.hpp"
#include <iostream>


Board::Board(int32_t width, int32_t height)
	: m_Width(width >> 1), m_Height(height), m_Size((width >> 1) * height)
{
	m_Board = new uint8_t[m_Size];
}

Board::~Board()
{
	delete[] m_Board;
}

void Board::draw_board() const
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD({ 0, 0 })); // go to 0 0

	uint8_t old_val = 255;
	for (uint32_t index = 0; index < m_Size; index++)
	{
		uint8_t cur_val = m_Board[index];
		if (cur_val != old_val)
		{
			old_val = cur_val;
			if (cur_val == 1)
				std::cout << "\x1b[47m";
			else
				std::cout << "\x1b[0m";
		}
		std::cout << "  ";
	}
}

void Board::step_simulation()
{
	// implement simulation step
}
