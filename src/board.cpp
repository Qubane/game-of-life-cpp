#include "headers/game.hpp"


Board::Board(int32_t width, int32_t height)
	: m_Width(width), m_Height(height), m_Size(width * height)
{
	m_Board = new uint8_t[m_Size];
}

Board::~Board()
{
	delete[] m_Board;
}
