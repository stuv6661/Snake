#include <MLV/MLV_all.h>

int main(int argc, char *argv[]){
	int coordonnee1_x[3] = {250, 370, 490};
	int coordonnee1_y[3] = {185, 130, 185};
		
	MLV_create_window( "beginner - 2 - shapes", "shapes", 640, 480 );
	MLV_draw_filled_rectangle(0,350,640,180, MLV_COLOR_GREEN );
	MLV_draw_filled_rectangle(0,0,640,350, MLV_COLOR_CYAN );	
	MLV_draw_filled_circle( 100, 60, 100, MLV_COLOR_YELLOW );
	MLV_draw_filled_rectangle( 250, 185, 240, 200, MLV_COLOR_RED );
	MLV_draw_filled_rectangle( 280, 250, 40, 80, MLV_COLOR_PURPLE );
	MLV_draw_filled_rectangle( 420, 250, 40, 80, MLV_COLOR_PURPLE );
	MLV_draw_filled_rectangle( 340, 270, 60, 110, MLV_COLOR_PURPLE );
	
	MLV_draw_filled_polygon( coordonnee1_x, coordonnee1_y, 3, MLV_COLOR_BLUE);
	
	MLV_actualise_window();
	MLV_actualise_window();
	MLV_actualise_window();
	MLV_wait_seconds( 5 );
	MLV_free_window();
	MLV_actualise_window();
	MLV_actualise_window();
	MLV_actualise_window();
	return 0;
}
