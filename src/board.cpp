#include "headers/game.hpp"
#include <iostream>
#include <string>


Game::Game(int32_t width, int32_t height)
	: m_Width(width >> 1), m_Height(height), m_Size((width >> 1) * height), m_DeltaTime(), m_CurrentTime(), m_Padding()
{
	// make board
	m_Board = new uint8_t[m_Size];

	// calculate padding (can only be 0 or 1)
	m_Padding = width % 2;
}

Game::~Game()
{
	delete[] m_Board;
}

void Game::update_clock()
{
	// calculate delta time
	m_DeltaTime = std::chrono::steady_clock::now() - m_CurrentTime;

	// update current time
	m_CurrentTime = std::chrono::steady_clock::now();
}

void Game::draw_board() const
{
	// go to 0, 0
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD({ 0, 0 }));

	// draw board
	uint8_t old_val = 255;
	std::string output = "";
	for (int32_t index = 0; index < m_Size - m_Width; index++)
	{
		// only update color when it changes
		uint8_t cur_val = m_Board[index];
		if (cur_val != old_val)
		{
			old_val = cur_val;
			if (cur_val == 1)
				output += "\x1b[47m";	// white
			else
				output += "\x1b[0m";	// black (reset)
		}

		// add spaces
		output += "  ";

		// add padding
		if (m_Padding > 0 && index % m_Width == 0 && index > 0)
			output += " ";
	}
	
	// add debug info
	// '\x1b[0m' - reset color
	// '\x1b[0K' - erase from cursor to end of line
	output += "\n\x1b[0m\x1b[0K" + std::to_string(m_DeltaTime.count() / 1000) + " ns";

	// printout
	std::cout << output;
}

const uint8_t Game::get_cell(int32_t x, int32_t y) const
{
	// bound check, if within bounds -> return cell, otherwise return 0
	if (x > -1 && x < m_Width && y > -1 && y < m_Height)
		return m_Board[x + y * m_Width];
	return 0;
}

void Game::set_cell(int32_t x, int32_t y, uint8_t val)
{
	// bound check, if within bounds -> set cell to given value
	if (x > -1 && x < m_Width && y > -1 && y < m_Height)
		m_Board[x + y * m_Width] = val;
}

void Game::step_simulation()
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

			// GoL rules
			if ((get_cell(x, y) == 1 && neighbors == 2) || neighbors == 3)
				new_board[x + y * m_Width] = 1;
		}
	}
	m_Board = new_board;
}
