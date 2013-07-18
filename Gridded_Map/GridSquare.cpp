
#include "GridSquare.h"



GridSquare::GridSquare(WorldObject* obj_to_set){
	is_object = false;
	object = obj_to_set;
}

GridSquare::GridSquare(int _x, int _y, WorldObject* obj_to_set)
{
	x = _x;   y = _y; 

	coord_x = grid_X(x) * pix_per_grid_block_x*pixToXCoord + graphXMin; 
	coord_y = -1*((grid_Y(y)+1) * pix_per_grid_block_y*pixToYCoord) + graphYMax; 
	width = pix_per_grid_block_x*pixToXCoord;
	height = pix_per_grid_block_y*pixToYCoord;

	is_object = false;
	object = obj_to_set;
}

GridSquare::~GridSquare(){
	delete object;
}

