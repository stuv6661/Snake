#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "grid.h"

void debug(char Mat[NBL][NBC],int l, int c)
{
	int i,j;
	for(i=0;i<l;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%c ",Mat[i][j]);
		}
		printf("\n");
	}
}

int compute_size (int width, int height)
{
	int a,b;
	a=width/NBC;
	b=height/NBL;
	if (b<a)
		a=b;
	return a;
}


void draw_grid(char grid[NBL][NBC])
{
	int width = MLV_get_desktop_width();
	int height = MLV_get_desktop_height();
	int i,j,a=compute_size(width,height),l=0,c=0;
	for(i=0;i<NBL;i++)
	{
		for(j=0;j<NBC;j++)
		{
			MLV_draw_text_box(c, l, a, a,
			MLV_convert_unicode_to_string("w"), 0, MLV_COLOR_WHITE,
			MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_CENTER,
			MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
			c+=a;
		}
		l+=a;
		c=0;
	}
	MLV_actualise_window();
	MLV_wait_seconds(3);
/*	MLV_free_window();
*/}
