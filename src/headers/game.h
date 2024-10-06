#pragma once
#include <stdint.h>


void run();


class Board
{
public:
	Board(uint32_t width, uint32_t height);
	~Board();

	void step_simulation();
	void poke_cell(uint32_t x, uint32_t y, uint8_t value);
	uint8_t get_cell(uint32_t x, uint32_t y);

	const uint32_t width() const { return m_Width; };
	const uint32_t height() const { return m_Height; };
private:
	uint32_t m_Width, m_Height;
	uint8_t* m_Board;
};
