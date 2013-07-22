
#include "GridSquare.h"



GridSquare::GridSquare(WorldObject* obj_to_set){
	is_object = false;
	thisContainsIGV = false;
	object = obj_to_set;
}

GridSquare::GridSquare(int _grid_x, int _grix_y, WorldObject* obj_to_set)
{
	grid_x = _grid_x;//grid_X(x) * pix_per_grid_block_x*pixToXCoord + graphXMin; 
	grid_y = _grix_y;//-1*((grid_Y(y)+1) * pix_per_grid_block_y*pixToYCoord) + graphYMax;

	coord_x = toX_Coord_From_GridCoord(grid_x);
	coord_y = toY_Coord_From_GridCoord(grid_y);

	width = pix_per_grid_block_x*pixToXCoord;
	height = pix_per_grid_block_y*pixToYCoord;

	is_object = false;
	thisContainsIGV = false;
	object = obj_to_set;
}

GridSquare::~GridSquare(){
	delete object;
}

