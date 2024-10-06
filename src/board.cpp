#include "headers/game.hpp"
#include <iostream>
#include <string>


Board::Board(int32_t width, int32_t height)
	: m_Width(width >> 1), m_Height(height), m_Size((width >> 1) * height), m_SimulationStep()
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

	std::string output = "";
	uint8_t old_val = 255;
	for (uint32_t index = 0; index < m_Size - m_Width; index++)
	{
		uint8_t cur_val = m_Board[index];
		if (cur_val != old_val)
		{
			old_val = cur_val;
			if (cur_val == 1)
				output += "\x1b[47m";
			else
				output += "\x1b[0m";
		}
		output += "  ";
	}
	output += std::to_string(m_SimulationStep);
	std::cout << output;
}

const uint8_t Board::get_cell(int32_t x, int32_t y) const
{
	if (x > -1 && x < m_Width && y > -1 && y < m_Height)
		return m_Board[x + y * m_Width];
	return 0;
}

void Board::set_cell(int32_t x, int32_t y, uint8_t val)
{
	if (x > -1 && x < m_Width && y > -1 && y < m_Height)
		m_Board[x + y * m_Width] = val;
}

void Board::step_simulation()
{
	// naive implementation
	uint8_t* new_board = new uint8_t[m_Size];
	for (int32_t y = 0; y < m_Height; y++)
	{
		for (int32_t x = 0; x < m_Width; x++)
		{
			// count neighbors
			uint8_t neighbors = 0;
			if (get_cell(x + 1, y + 1) == 1) neighbors++;  // 1   1
			if (get_cell(x + 0, y + 1) == 1) neighbors++;  // 0   1
			if (get_cell(x - 1, y + 1) == 1) neighbors++;  // -1  1

			if (get_cell(x + 1, y + 0) == 1) neighbors++;  // 1   0
			if (get_cell(x - 1, y + 0) == 1) neighbors++;  // -1  0

			if (get_cell(x + 1, y - 1) == 1) neighbors++;  // 1  -1
			if (get_cell(x + 0, y - 1) == 1) neighbors++;  // 0  -1
			if (get_cell(x - 1, y - 1) == 1) neighbors++;  // -1 -1

			if ((get_cell(x, y) == 1 && neighbors == 2) || neighbors == 3)
				new_board[x + y * m_Width] = 1;
		}
	}
	m_Board = new_board;
	m_SimulationStep++;
}
