
#include "IGV_Bot.h"

IGV_Bot::IGV_Bot(){ 
	x = 100; 				//px
	y = 100;
	searchRadius = 120; //px

	// pixels
	width = 50;
	height = 50;


	//coord units
	width_coord = 1;
	height_coord = 1;

	draw_coord_x = 0;
	draw_coord_y = 0;

}


void IGV_Bot::moveTo(int _x, int _y){
	if (_x > window.width)
		_x = window.width;
	if (_x < 0)
		_x = 0;
	if (_y > window.height)
		_y = window.height;
	if (_y < 0)
		_y = 0;

	x = _x;
	y = _y;

	coord_x = toX_Coord(_x);
	coord_y = toY_Coord(_y);

	draw_coord_x = coord_x - (width_coord/2);
	draw_coord_y = coord_y - (height_coord/2);
}