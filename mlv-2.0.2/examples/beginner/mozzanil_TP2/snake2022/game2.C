#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "grid.h"

int main()
{
	char grid[8][7] =
	{
		"bwrwbw",
		"wrwbwr",
		"bwrwbw",
		"wrwbwr",
		"bwrwbw",
		"wrwbwr",
		"bwrwbw",
		"wrwbwr"
	};
	int width = 640, height = 480;
	MLV_create_window( "SNAKE", "3R-IN1B", width, height );
	MLV_change_frame_rate( 24 );
	draw_grid(grid);
	return 0;
}
