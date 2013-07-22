
#include "IGV_Bot.h"


/* default */
IGV_Bot::IGV_Bot() : WorldObject(50, 50) 
{ 
    init(); 
}

/* explicit */
IGV_Bot::IGV_Bot(int _x, int _y, unsigned char _type) : WorldObject(_x, _y, _type)
{ 

	init();
}


void IGV_Bot::init(){ 

	searchRadius = 72; //px

	// shape in pixels
	width = 18;
	height = 18;

	// shpe in graph coord units
	width_coord = pixToXCoord * width;
	height_coord = pixToYCoord * height;

	// where to draw.. drawing coordinates
	draw_coord_x = coord_x - (width_coord/2);  //current coord but offset left and down..  
	draw_coord_y = coord_y - (height_coord/2); // by the Width & height

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




void IGV_Bot::glow(){ 
    perform_glow_effect_grid(coord_x, coord_y, width, height); 
}

