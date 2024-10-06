#include "headers/game.h"


void run()
{
	Board board(120, 30);
	while (true)
	{
		// terminal.draw();
		board.step_simulation();
	}
}
