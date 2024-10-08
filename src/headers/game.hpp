#pragma once
#include <stdint.h>
#include <chrono>


// Taken from 'https://stackoverflow.com/a/62485211'
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux

void run();


class Game
{
public:
	Game(int32_t width, int32_t height);
	~Game();

	void update_clock();
	void draw_board() const;
	void step_simulation();

	void set_cell(int32_t x, int32_t y, uint8_t val);
	const uint8_t get_cell(int32_t x, int32_t y) const;

	uint8_t* m_Board = nullptr;
	const int32_t m_Width, m_Height, m_Size;

	std::chrono::steady_clock::time_point m_CurrentTime;
	std::chrono::nanoseconds m_DeltaTime;
};
