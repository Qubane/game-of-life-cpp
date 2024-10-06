#include "headers/terminal.h"
#include "headers/game.h"


void run()
{
	Board board(120, 30);
	Terminal terminal;

	board.poke_cell(2, 2, 1);

	while (true)
	{
		terminal.draw(board);
		board.step_simulation();
	}
}
