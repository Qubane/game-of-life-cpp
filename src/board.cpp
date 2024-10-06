#include "headers/game.h"
#include <stdint.h>


Board::Board(uint32_t width, uint32_t height)
	: m_Width(width), m_Height(height)
{
	m_Board = new uint8_t[(uint64_t)width * height];
}

Board::~Board()
{
	delete[] m_Board;
}

void Board::poke_cell(uint32_t x, uint32_t y, uint8_t value)
{
	if (x > -1 && x < m_Width && y > -1 && y < m_Height)
		m_Board[x + y * m_Width] = value;
}

const uint8_t Board::get_cell(uint32_t x, uint32_t y) const
{
	if (x > -1 && x < m_Width && y > -1 && y < m_Height)
		return m_Board[x + y * m_Width];
}

const uint8_t Board::get_cell(uint64_t index) const
{
	if (index < m_Width * m_Height)
		return m_Board[index];
}

void Board::step_simulation()
{
	// do something here
}
